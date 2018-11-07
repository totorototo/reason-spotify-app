let component = ReasonReact.statelessComponent("Track");

let make = (~track, _children) => {
  ...component,
  render: _self =>
    <div style=Styles.card>
      <section style=Styles.cardHeader>
        <div style=Styles.cardAvatar />
        <div>
          <p style=Styles.cardTitle> {track##name |> ReasonReact.string} </p>
        </div>
      </section>
      <section style=Styles.cardMedia>
        <div style=Styles.cardMaterialImage width="262" height="262" />
      </section>
      <section style=Styles.cardSupportingText>
        {
          "Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas."
          |> ReasonReact.string
        }
      </section>
    </div>,
};