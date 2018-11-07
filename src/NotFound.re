let component = ReasonReact.statelessComponent("NotFound");

let make = _children => {
  ...component,
  render: _self =>
    <div>
      <span>
        {
          ReasonReact.string(
            "The page you're looking for can't be found. Go home by ",
          )
        }
      </span>
      <Link href="/Login"> {ReasonReact.string("clicking here!")} </Link>
    </div>,
};