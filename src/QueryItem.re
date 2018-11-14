type query = {
  id: string,
  title: string,
  completed: bool,
};

type state = {
  editText: string,
  editing: bool,
  editFieldRef: ref(option(Dom.element)),
};

type action =
  | Edit
  | Submit
  | KeyDown(int)
  | Change(string);

let component = ReasonReact.reducerComponent("QueryItem");

let setEditFieldRef = (r, {ReasonReact.state}) =>
  state.editFieldRef := Js.Nullable.toOption(r);

let make =
    (
      ~query,
      ~editing,
      ~onDestroy,
      ~onSave,
      ~onEdit,
      ~onToggle,
      ~onCancel,
      _children,
    ) => {
  let submitHelper = state =>
    switch (String.trim(state.editText)) {
    | "" => ReasonReact.SideEffects((_self => onDestroy()))
    | nonEmptyValue =>
      ReasonReact.UpdateWithSideEffects(
        {...state, editText: nonEmptyValue},
        (_self => onSave(nonEmptyValue)),
      )
    };
  {
    ...component,
    initialState: () => {editText: "", editFieldRef: ref(None), editing},
    reducer: action =>
      switch (action) {
      | Edit => (state => ReasonReact.Update({...state, editText: ""}))
      | Submit => submitHelper
      | Change(text) => (
          state =>
            editing ?
              ReasonReact.Update({...state, editText: text}) :
              ReasonReact.NoUpdate
        )
      | KeyDown(27) =>
        onCancel();
        (state => ReasonReact.Update({...state, editText: ""}));
      | KeyDown(13) => submitHelper
      | KeyDown(_) => (_state => ReasonReact.NoUpdate)
      },
    willReceiveProps: ({state}) => {...state, editing},
    didUpdate: ({oldSelf, newSelf}) =>
      switch (oldSelf.state.editing, editing, newSelf.state.editFieldRef^) {
      | (false, true, Some(field)) =>
        let node = ReactDOMRe.domElementToObj(field);
        ignore(node##focus());
        ignore(
          node##setSelectionRange(node##value##length, node##value##length),
        );
      | _ => ()
      },
    /* escape key */
    render: ({state, handle, send}) => {
      let toto = "";
      let className =
        [query.completed ? "completed" : "", editing ? "editing" : ""]
        |> String.concat(" ");
      <li className>
        <div className="view">
          <input
            className="toggle"
            type_="checkbox"
            checked={query.completed}
            onChange={_ => onToggle()}
          />
          <label
            onDoubleClick={
              _event => {
                onEdit();
                send(Edit);
              }
            }>
            {ReasonReact.string(query.title)}
          </label>
          <button className="destroy" onClick={_ => onDestroy()} />
        </div>
        <input
          className="edit"
          ref={handle(setEditFieldRef)}
          value={state.editText}
          onBlur={_event => send(Submit)}
          onChange={
            event => send(Change(ReactEvent.Form.target(event)##value))
          }
          onKeyDown={
            event => send(KeyDown(ReactEvent.Keyboard.which(event)))
          }
        />
      </li>;
    },
  };
};