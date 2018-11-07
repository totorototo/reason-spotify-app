let handleClick = (href, event) =>
  if (! ReactEvent.Mouse.defaultPrevented(event)) {
    ReactEvent.Mouse.preventDefault(event);
    ReasonReact.Router.push(href);
  };

let component = ReasonReact.statelessComponent("Link");

let make = (~href, ~className="", children) => {
  ...component,
  render: _self =>
    <a href className onClick=(handleClick(href))> ...children </a>
};