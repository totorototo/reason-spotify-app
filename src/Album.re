let component = ReasonReact.statelessComponent("Album");

let make = (~album, _children) => {
  ...component,
  render: _self =>
    <div style=Styles.card>
      <section style=Styles.cardHeader>
        <div style=Styles.cardAvatar />
        <div>
          <p style=Styles.cardTitle>
            {album##album_type |> ReasonReact.string}
          </p>
          <p style=Styles.cardSubtitle>
            {album##name |> ReasonReact.string}
          </p>
        </div>
      </section>
      <section style=Styles.cardMedia>
        <div style=Styles.cardMaterialImage width="262" height="262">
          <img style=Styles.cardImage src=album##images[1]##url />
        </div>
      </section>
      <section style=Styles.cardSupportingText>
        {
          "Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas."
          |> ReasonReact.string
        }
      </section>
    </div>,
};