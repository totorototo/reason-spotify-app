let container =
  ReactDOMRe.Style.make(~display="flex", ~flex="1", ~flexDirection="row", ());

let queriesContainer =
  ReactDOMRe.Style.make(
    ~display="flex",
    ~flex="1",
    ~flexDirection="column",
    ~width={|25%|},
    (),
  );

let resultsContainer =
  ReactDOMRe.Style.make(
    ~backgroundColor="#FFFFFF",
    ~color="#1DB954",
    ~display="flex",
    ~flexDirection="row",
    ~flexWrap="wrap",
    ~justifyContent="center",
    ~alignItems="center",
    ~fontFamily={|Roboto|},
    ~width={|75%|},
    (),
  );

let searchResult =
  ReactDOMRe.Style.make(
    ~backgroundColor="#FFFFFF",
    ~color="#1DB954",
    ~display="flex",
    ~flexDirection="row",
    ~flexWrap="wrap",
    ~justifyContent="center",
    ~alignItems="center",
    ~fontFamily={|Roboto|},
    ~width={|75%|},
    (),
  );

let searchParameters =
  ReactDOMRe.Style.make(
    ~display="flex",
    ~flex="1",
    ~flexDirection="column",
    ~width={|25%|},
    (),
  );

let loginContainer =
  ReactDOMRe.Style.make(
    ~backgroundColor="#FFFFFF",
    ~display="flex",
    ~flex="1",
    ~flexDirection="column",
    ~justifyContent="center",
    ~alignItems="center",
    ~fontFamily="Roboto",
    ~alignContent="flex-end",
    (),
  );

let toolbarStyle =
  ReactDOMRe.Style.make(
    ~margin="40px",
    ~padding="5px",
    ~backgroundColor="#1DB954",
    ~color="#FFFFFF",
    ~borderWidth="0px",
    ~borderRadius="500px",
    ~lineHeight="1px",
    ~fontSize="14px",
    ~letterSpacing="2px",
    ~minWidth="160px",
    ~paddingTop="18px",
    ~paddingRight="48px",
    ~paddingLeft="48px",
    ~paddingBottom="16px",
    ~transitionProperty=
      {|background-color,border-color,color,box-shadow,filter|},
    ~transitionDuration={|.3s|},
    ~fontFamily={|Roboto|},
    ~flexWrap="wrap",
    (),
  );

let left =
  ReactDOMRe.Style.make(
    ~color="#000000",
    ~fontSize="40px",
    ~fontFamily="Roboto",
    ~display="flex",
    ~fontWeight="300",
    ~flexDirection="column",
    ~alignItems="flex-end",
    (),
  );
let right =
  ReactDOMRe.Style.make(
    ~color="#000000",
    ~fontSize="80px",
    ~fontFamily={|Roboto Condensed|},
    ~fontWeight="600",
    ~margin="5px",
    (),
  );

let titleContainer =
  ReactDOMRe.Style.make(~display="flex", ~flexDirection="row", ());

let card =
  ReactDOMRe.Style.make(
    ~backgroundColor="#EEEEEE",
    ~color="#616161",
    ~display="flex",
    ~flexDirection="column",
    ~justifyContent="flex-end",
    ~alignItems="center",
    ~fontFamily={|Roboto|},
    ~fontSize="14px",
    ~fontWeight="400px",
    ~paddingBottom="0",
    ~margin="10px",
    ~height="290px",
    ~width="262px",
    ~boxShadow=
      {|0 3px 1px -2px rgba(0,0,0,.2),0 2px 2px 0 rgba(0,0,0,.14),0 1px 5px 0 rgba(0,0,0,.12)|},
    (),
  );

let cardHeader =
  ReactDOMRe.Style.make(
    ~alignItems="center",
    ~display="flex",
    ~padding={|0 16px 20px|},
    ~alignSelf="flex-start",
    (),
  );

let cardAvatar =
  ReactDOMRe.Style.make(
    ~backgroundColor="#bdbdbd",
    ~height="40px",
    ~width="40px",
    ~marginRight="12px",
    ~borderRadius={|50%|},
    (),
  );

let cardMedia =
  ReactDOMRe.Style.make(
    ~height="140px",
    ~overflow="hidden",
    ~padding="0",
    ~display="flex",
    ~flexDirection="column",
    ~justifyContent="flex-end",
    ~boxSizing="border-box",
    (),
  );

let cardMaterialImage =
  ReactDOMRe.Style.make(~position="relative", ~overflow="hidden", ());

let cardImage =
  ReactDOMRe.Style.make(
    ~width="100%",
    ~height="100%",
    ~objectFit="cover",
    (),
  );

let cardSupportingText =
  ReactDOMRe.Style.make(
    ~fontSize="10px",
    ~boxSizing="border-box",
    ~padding={|8px 16px|},
    ~fontWeight="400",
    ~letterSpacing=".04em",
    ~lineHeight="1.25rem",
    (),
  );

let cardTitle =
  ReactDOMRe.Style.make(~fontSize="11px", ~lineHeight="17px", ());

let cardSubtitle =
  ReactDOMRe.Style.make(~fontSize="11px", ~lineHeight="17px", ());

let paragraph =
  ReactDOMRe.Style.make(
    ~color="#616161",
    ~fontSize="14px",
    ~fontWeight="400",
    ~paddingBottom="0",
    (),
  );