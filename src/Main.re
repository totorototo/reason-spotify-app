let component = ReasonReact.statelessComponent("Main");

let make = (_children, ~token) => {
  ...component,
  render: _self =>
    <ReasonApollo.Provider client={Client.getInstance(token)}>
      <Search />
    </ReasonApollo.Provider>,
};