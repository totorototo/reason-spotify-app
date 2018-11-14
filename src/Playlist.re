let card =
  ReactDOMRe.Style.make(
    ~backgroundColor="#E91E63",
    ~color="#FFE0B2",
    ~display="flex",
    ~flexDirection="column",
    ~alignItems="flex-start",
    ~fontFamily={|Roboto|},
    ~fontSize="14px",
    ~fontWeight="400px",
    ~paddingBottom="0",
    ~margin="10px",
    ~height="290px",
    ~width="262px",
    ~overflow="hidden",
    ~borderRadius="5px",
    ~boxShadow=
      {|0 3px 1px -2px rgba(0,0,0,.2),0 2px 2px 0 rgba(0,0,0,.14),0 1px 5px 0 rgba(0,0,0,.12)|},
    (),
  );

let newCard =
  ReactDOMRe.Style.make(
    ~transition=".3",
    ~boxShadow={|0 4px 8px 0 rgba(0,0,0,0.2)|},
    (),
  );

let container = ReactDOMRe.Style.make(~padding={|2px 16px|}, ());

let title =
  ReactDOMRe.Style.make(
    ~fontSize="25px",
    ~marginLeft="20px",
    ~lineHeight="27px",
    ~fontWeight="900px",
    (),
  );

let subTitle =
  ReactDOMRe.Style.make(
    ~fontSize="12px",
    ~marginLeft="20px",
    ~lineHeight="14px",
    (),
  );

let backGround =
  ReactDOMRe.Style.make(
    ~fontSize="60px",
    ~opacity="0.25",
    ~alignSelf="center",
    ~marginTop="20px",
    (),
  );

let link =
  ReactDOMRe.Style.make(
    ~fontSize="12px",
    ~color="#FFFFFF",
    ~fontFamily="Roboto",
    ~marginLeft="20px",
    (),
  );

let component = ReasonReact.statelessComponent("Playlist");

let make = (~playlist, _children) => {
  ...component,
  render: _self =>
    <div style=card>
      <div style=backGround> {"Playlist" |> ReasonReact.string} </div>
      <section>
        <div style=title> {playlist##name |> ReasonReact.string} </div>
        <div style=subTitle>
          {playlist##owner##display_name |> ReasonReact.string}
        </div>
      </section>
    </div>,
};