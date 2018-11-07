let matchAccessToken = [%re "/access_token=([^\\$&]+)/g"];

let matchExpiresIn = [%re "/expires_in=([^\\$&]+)/g"];

let matchIdToken = [%re "/id_token=([^\\$&]+)/g"];

let resolveOption = opt =>
  switch opt {
  | None => ""
  | Some(s) => s
  };

let resolveRegex = (exp, str) => {
  let res = exp |> Js.Re.exec(str);
  switch res {
  | None => ""
  | Some(result) =>
    let captures = result |> Js.Re.captures;
    switch captures {
    | [|_, token|] => token |> Js.Nullable.toOption |> resolveOption
    | _ => ""
    };
  };
};

let handleAuth = (url: ReasonReact.Router.url) =>
  url.hash |> resolveRegex(matchAccessToken);