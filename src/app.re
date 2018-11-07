type route =
  | Main
  | Login
  | Callback(ReasonReact.Router.url)
  | NotFound;

type token = string;

type isUserAuthorized = bool;

type state = {
  route,
  token,
  isUserAuthorized,
};

type action =
  | ChangeRoute(route)
  | UpdateToken(token);

let reducer = (action, state) =>
  switch (action) {
  | ChangeRoute(route) =>
    ReasonReact.Update({...state, route, isUserAuthorized: true})
  | UpdateToken(token) =>
    ReasonReact.UpdateWithSideEffects(
      {...state, token},
      (_self => ReasonReact.Router.push("/Main")),
    )
  };

let mapUrlToRoute = (url: ReasonReact.Router.url) =>
  switch (url.path) {
  | [] => Login
  | ["Login"] => Login
  | ["Main"] => Main
  | ["callback"] => Callback(url)
  | _ => Login
  };

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  reducer,
  initialState: () => {route: Login, token: "", isUserAuthorized: false},
  didMount: self => {
    let watcherID =
      ReasonReact.Router.watchUrl(url =>
        self.send(ChangeRoute(url |> mapUrlToRoute))
      );
    self.onUnmount(() => ReasonReact.Router.unwatchUrl(watcherID));
  },
  render: self => {
    Js.log(self.state.token);
    switch (self.state.route, self.state.isUserAuthorized) {
    | (Main, true) => <Main token={self.state.token} />
    | (Main, false) => <Login />
    | (Login, _) => <Login />
    | (NotFound, true) => <NotFound />
    | (NotFound, false) => <Login />
    | (Callback(url), _) =>
      <Callback url dispatch=(token => self.send(UpdateToken(token))) />
    };
  },
};