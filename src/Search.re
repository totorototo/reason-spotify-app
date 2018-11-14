open Belt;

[%bs.raw {|require('./style.css')|}];

[@bs.val] external unsafeJsonParse: string => 'a = "JSON.parse";

let localStorageNamespace = "reason-spotify-app";

let saveLocally = queries =>
  switch (Js.Json.stringifyAny(queries)) {
  | None => ()
  | Some(stringifiedQueries) =>
    Dom.Storage.(
      localStorage |> setItem(localStorageNamespace, stringifiedQueries)
    )
  };

let main =
  ReactDOMRe.Style.make(
    ~position="relative",
    ~zIndex="2",
    ~borderTop={|1px solid #e6e6e6|},
    (),
  );

let toggleAll =
  ReactDOMRe.Style.make(
    ~width="1px",
    ~height="1px",
    ~border="none",
    ~opacity="0",
    ~position="absolute",
    ~right="100%",
    ~bottom="100%",
    (),
  );

let queryList =
  ReactDOMRe.Style.make(~margin="0", ~padding="0", ~listStyle="none", ());

let queryListItem =
  ReactDOMRe.Style.make(
    ~position="relative",
    ~fontSize="24px",
    ~borderBottom={|1px solid #ededed|},
    (),
  );

type showingState =
  | AllQueries
  | ActiveQueries
  | CompletedQueries;

type action =
  /* query actions */
  | NewQueryEnterKeyDown
  | NewQueryOtherKeyDown
  | ClearCompleted
  | Cancel
  | ChangeQuery(string)
  | Save(QueryItem.query, string)
  | Edit(QueryItem.query)
  | Destroy(QueryItem.query)
  | Toggle(QueryItem.query)
  | ToggleAll(bool);

type state = {
  editing: option(string),
  newQuery: string,
  queries: list(QueryItem.query),
  nowShowing: showingState,
};

let component = ReasonReact.reducerComponent("Query");
let make = _children => {
  ...component,
  reducer: (action, state) =>
    switch (action) {
    | Cancel => ReasonReact.Update({...state, editing: None})
    | ChangeQuery(text) => ReasonReact.Update({...state, newQuery: text})
    | NewQueryOtherKeyDown => ReasonReact.NoUpdate
    | NewQueryEnterKeyDown =>
      switch (String.trim(state.newQuery)) {
      | "" => ReasonReact.NoUpdate
      | nonEmptyValue =>
        let queries =
          state.queries
          @ [
            {
              id: string_of_float(Js.Date.now()),
              title: nonEmptyValue,
              completed: false,
            },
          ];
        saveLocally(queries);
        ReasonReact.Update({...state, newQuery: "", queries});
      }
    | ClearCompleted =>
      let queries =
        List.keep(state.queries, query => !QueryItem.(query.completed));
      ReasonReact.UpdateWithSideEffects(
        {...state, queries},
        (_self => saveLocally(queries)),
      );
    | ToggleAll(checked) =>
      let queries =
        List.map(state.queries, query =>
          {...query, QueryItem.completed: checked}
        );
      ReasonReact.UpdateWithSideEffects(
        {...state, queries},
        (_self => saveLocally(queries)),
      );
    | Save(queryToSave, text) =>
      let queries =
        List.map(state.queries, query =>
          query == queryToSave ? {...query, QueryItem.title: text} : query
        );
      ReasonReact.UpdateWithSideEffects(
        {...state, editing: None, queries},
        (_self => saveLocally(queries)),
      );
    | Edit(query) =>
      ReasonReact.Update({...state, editing: Some(QueryItem.(query.id))})
    | Destroy(query) =>
      let queries = List.keep(state.queries, candidate => candidate !== query);
      ReasonReact.UpdateWithSideEffects(
        {...state, queries},
        (_self => saveLocally(queries)),
      );
    | Toggle(queryToToggle) =>
      let queries =
        List.map(state.queries, query =>
          query == queryToToggle ?
            {...query, QueryItem.completed: !QueryItem.(query.completed)} :
            query
        );
      ReasonReact.UpdateWithSideEffects(
        {...state, queries},
        (_self => saveLocally(queries)),
      );
    },
  initialState: () => {
    let queries =
      switch (Dom.Storage.(localStorage |> getItem(localStorageNamespace))) {
      | None => []
      | Some(queries) => unsafeJsonParse(queries)
      };
    {editing: None, newQuery: "", queries, nowShowing: AllQueries};
  },
  /* router actions */
  render: ({state, send}) => {
    let {queries, editing} = state;

    let param =
      List.reduceWithIndex(
        state.queries,
        "",
        (accu, current, index) => {
          let result =
            if (index == 0) {
              accu ++ current.title;
            } else {
              accu ++ {|%20|} ++ current.title;
            };
          result;
        },
      );

    let queryItems =
      List.keep(queries, query =>
        QueryItem.(
          switch (state.nowShowing) {
          | ActiveQueries => !query.completed
          | CompletedQueries => query.completed
          | AllQueries => true
          }
        )
      )
      |> List.map(
           _,
           query => {
             let editing =
               switch (editing) {
               | None => false
               | Some(editing) => editing === QueryItem.(query.id)
               };
             <QueryItem
               key={query.id}
               query
               onToggle={_event => send(Toggle(query))}
               onDestroy={_event => send(Destroy(query))}
               onEdit={_event => send(Edit(query))}
               editing
               onSave={text => send(Save(query, text))}
               onCancel={_event => send(Cancel)}
             />;
           },
         );
    let queriesLength = List.length(queries);
    let completedCount =
      List.keep(queries, query => QueryItem.(query.completed)) |> List.length;
    let activeTodoCount = queriesLength - completedCount;

    <div style=Styles.container>
      <div style=Styles.queriesContainer>
        <header className="header">
          <input
            className="new-query"
            placeholder="What are you looking for ?"
            value={state.newQuery}
            onKeyDown={
              event =>
                if (ReactEvent.Keyboard.keyCode(event) === 13) {
                  ReactEvent.Keyboard.preventDefault(event);
                  send(NewQueryEnterKeyDown);
                } else {
                  send(NewQueryOtherKeyDown);
                }
            }
            onChange={
              event =>
                send(ChangeQuery(ReactEvent.Form.target(event)##value))
            }
            autoFocus=true
          />
          {
            queriesLength === 0 ?
              ReasonReact.null :
              <section className="main">
                <input
                  className="toggle-all"
                  type_="checkbox"
                  onChange={
                    event => {
                      let checked = ReactEvent.Form.target(event)##checked;
                      send(ToggleAll(checked));
                    }
                  }
                  checked={activeTodoCount === 0}
                />
                <ul className="query-list">
                  {ReasonReact.array(List.toArray(queryItems))}
                </ul>
              </section>
          }
        </header>
      </div>
      <div style=Styles.resultsContainer> <Query param /> </div>
    </div>;
  },
};