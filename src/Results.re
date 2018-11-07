[@bs.module] external gql: ReasonApolloTypes.gql = "graphql-tag";

module SearchItems = [%graphql
  {|
  query searchItems($queryParam: String, $typeParam: String) {
    search(queryParam: $queryParam, typeParam: $typeParam) {
      ... on Artist {
        type
        id
        genres
        name
      }

      ... on Album {
        type
        id
        name
        album_type
        release_date
        images{
          url
        }
      }

      ... on Playlist {
        id
        name
        type
        owner {
          display_name
          id
        }
      }

      ... on Track {
        type
        name
        id
      }
    }
  }
|}
];

module SearchItemsQuery = ReasonApollo.CreateQuery(SearchItems);

let component = ReasonReact.statelessComponent("Results");

let make = (~query, _children) => {
  ...component,
  render: _self => {
    let searchItemsQuery =
      SearchItems.make(
        ~typeParam={|album,artist,playlist,track|},
        ~queryParam=query,
        (),
      );

    <SearchItemsQuery variables=searchItemsQuery##variables>
      ...{
           ({result}) =>
             switch (result) {
             | Loading => <div> {"Loading" |> ReasonReact.string} </div>
             | Error(_e) => <div> {"Error" |> ReasonReact.string} </div>
             | Data(response) => <div style=Styles.searchResult />
             }
         }
    </SearchItemsQuery>;
  },
};