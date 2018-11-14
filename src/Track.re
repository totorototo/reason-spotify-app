let card =
  ReactDOMRe.Style.make(
    ~backgroundColor="#3F51B5",
    ~color="#FFE0B2",
    ~display="flex",
    ~flexDirection="column",
    ~justifyContent="center",
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
    ~position="absolute",
    ~fontSize="180px",
    ~opacity="0.25",
    ~alignSelf="center",
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

let component = ReasonReact.statelessComponent("Track");

let make = (~track, _children) => {
  ...component,
  render: _self =>
    <div style=card>
      <div style=backGround>
        {ReasonReact.string(string_of_int(track##popularity))}
      </div>
      <section>
        <p style=title> {track##name |> ReasonReact.string} </p>
      </section>
    </div>,
};