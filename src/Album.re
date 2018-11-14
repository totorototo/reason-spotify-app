let card =
  ReactDOMRe.Style.make(
    ~backgroundColor="#FF9800",
    ~color="#FFE0B2",
    ~display="flex",
    ~flexDirection="column",
    ~justifyContent="flex-start",
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
    ~fontWeight="300px",
    ~margin="15px",
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
    ~margin="15px",
    ~fontSize="40px",
    ~opacity="0.25",
    (),
  );

let divider =
  ReactDOMRe.Style.make(
    ~height="1px",
    ~width="100%",
    ~backgroundColor="#FFFFFF",
    ~color="#FFFFFF",
    ~opacity=".3",
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

let component = ReasonReact.statelessComponent("Album");

let make = (~album, _children) => {
  ...component,
  render: _self =>
    <div style=card>
      <div style=title> {album##name |> ReasonReact.string} </div>
      <div style=divider />
      <section>
        <p style=subTitle> {album##name |> ReasonReact.string} </p>
        <p style=subTitle> {album##release_date |> ReasonReact.string} </p>
        <a style=link href=album##external_urls##spotify target="_blank">
          {album##album_type |> ReasonReact.string}
        </a>
      </section>
    </div>,
};