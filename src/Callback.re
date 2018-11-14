let component = ReasonReact.statelessComponent("Callback");

let make = (~url, ~dispatch, _children) => {
  ...component,
  didMount: _self => {
    let token = Authenticate.handleAuth(url);
    dispatch(token);
    ();
  },
  render: _self => <div> {"CallBack" |> ReasonReact.string} </div>,
};