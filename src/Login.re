type state =
  | Logging
  | Error
  | Logged
  | Idle;

type action =
  | GetCredentials
  | GotCrendentials
  | FailedToGetCrendential;

let url = {|https://accounts.spotify.com/authorize?client_id=864d590d605541b2b2fbaa61047cb7dd&redirect_uri=http://localhost:3000/callback&response_type=token&state=123|};

let redirect: string => unit = [%bs.raw
  {|
function (url) {
  window.location = url
}
|}
];

let component = ReasonReact.reducerComponent("Login");

let make = _children => {
  ...component,
  initialState: _state => Idle,
  reducer: (action, _state) =>
    switch (action) {
    | GetCredentials =>
      ReasonReact.UpdateWithSideEffects(Logging, (_self => redirect(url)))
    | GotCrendentials => ReasonReact.Update(Logged)
    | FailedToGetCrendential => ReasonReact.Update(Error)
    },
  render: self =>
    switch (self.state) {
    | Idle =>
      <div style=Styles.loginContainer>
        <div style=Styles.titleContainer>
          <div style=Styles.left>
            <div> {"Reason" |> ReasonReact.string} </div>
            <div> {"application" |> ReasonReact.string} </div>
          </div>
          <div style=Styles.right> {"Spotify" |> ReasonReact.string} </div>
        </div>
        <button
          style=Styles.toolbarStyle
          onClick=(_event => self.send(GetCredentials))>
          {"Connect" |> ReasonReact.string}
        </button>
      </div>
    | Error =>
      <div style=Styles.loginContainer>
        {"An error occurred!" |> ReasonReact.string}
      </div>
    | Logging =>
      <div style=Styles.loginContainer>
        {"Loggin...!" |> ReasonReact.string}
      </div>
    | Logged =>
      <div style=Styles.loginContainer>
        {"Logged...!" |> ReasonReact.string}
      </div>
    },
};