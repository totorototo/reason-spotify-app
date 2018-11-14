[@bs.module] external gql: ReasonApolloTypes.gql = "graphql-tag";

module SearchItems = [%graphql
  {|
  query searchItems($queryParam: String!, $typeParam: String!) {
    search(queryParam: $queryParam, typeParam: $typeParam) {
      ... on Artist {
        type
        id
        name
        popularity
        genres
        followers{
          total
        }
      }
      ... on Album {
        type
        id
        name
        album_type
        release_date
        artists{
          name
        }
        external_urls{
          spotify
        }
        label
      }
      ... on Playlist {
        id
        type
        name
        owner{
          display_name
        }
        images{
          url
        }
        collaborative
      }
      ... on Track {
        type
        id
        name
        disc_number
        duration_ms
        popularity
        track_number
        preview_url
      }
    }
  }
|}
];

module SearchItemsQuery = ReasonApollo.CreateQuery(SearchItems);

let component = ReasonReact.statelessComponent("Results");

let make = (~param, _children) => {
  ...component,
  render: _self => {
    let searchItemsQuery =
      SearchItems.make(
        ~typeParam={|album,artist,playlist,track|},
        ~queryParam=param,
        (),
      );

    <SearchItemsQuery variables=searchItemsQuery##variables>
      ...{
           ({result}) =>
             switch (result) {
             | Loading => <div> {"Loading" |> ReasonReact.string} </div>
             | Error(_e) => <div> {"Error" |> ReasonReact.string} </div>
             | Data(response) =>
               <div style=Styles.searchResult>
                 {
                   switch (response##search) {
                   | None => <div> {"Loading" |> ReasonReact.string} </div>
                   | Some(matches) =>
                     let realMatches =
                       matches->Belt.Array.keepMap(match => match);
                     realMatches->Belt.Array.map(item =>
                       switch (item) {
                       | `Album(album) => <Album album />
                       | `Artist(artist) => <Artist artist />
                       | `Track(track) => <Track track />
                       | `Playlist(playlist) => <Playlist playlist />
                       }
                     )
                     |> ReasonReact.array;
                   }
                 }
               </div>
             }
         }
    </SearchItemsQuery>;
  },
};