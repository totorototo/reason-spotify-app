open Belt;
let component = ReasonReact.statelessComponent("QueryItem");

let make =
    (
      _children,
      ~editing,
      ~newQuery,
      ~nowShowing: Search.showingState,
      ~queries,
      ~onToggle,
      ~onDestroy,
      ~onEdit,
      ~onSave,
      ~onCancel,
      ~onNewQueryEnterKeyDown,
      ~onNewQueryOtherKeyDown,
      ~onChangeQuery,
      ~onToggleAll,
    ) => {
  ...component,
  render: _self => {
    let queryItems =
      List.keep(queries, query =>
        QueryItem.(
          switch (nowShowing) {
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
               onToggle={onToggle(query)}
               onDestroy={onDestroy(query)}
               onEdit={onEdit(query)}
               editing
               onSave
               onCancel
             />;
           },
         );
    let queriesLength = List.length(queries);
    let completedCount =
      List.keep(queries, query => QueryItem.(query.completed)) |> List.length;
    let activeTodoCount = queriesLength - completedCount;

    <div style=Styles.queriesContainer>
      <header>
        <input
          placeholder="What are you looking for ?"
          value=newQuery
          onKeyDown={
            event =>
              if (ReactEvent.Keyboard.keyCode(event) === 13) {
                ReactEvent.Keyboard.preventDefault(event);
                onNewQueryEnterKeyDown;
              } else {
                onNewQueryOtherKeyDown;
              }
          }
          onChange={
            event => onChangeQuery(ReactEvent.Form.target(event)##value)
          }
          autoFocus=true
        />
      </header>
      {
        queriesLength === 0 ?
          ReasonReact.null :
          <section>
            <input
              type_="checkbox"
              onChange={
                event => {
                  let checked = ReactEvent.Form.target(event)##checked;
                  onToggleAll(checked);
                }
              }
              checked={activeTodoCount === 0}
            />
            <ul> {ReasonReact.array(List.toArray(queryItems))} </ul>
          </section>
      }
    </div>;
  },
};