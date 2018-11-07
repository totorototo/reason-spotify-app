/* Create an InMemoryCache */
let inMemoryCache = ApolloInMemoryCache.createInMemoryCache();

/* Create a Link that puts an Authorization header in context */
let headerContextLink = token => {
  let contextHandler = x => {
    let headers = {
      "headers": {
        "Authorization": {j|Bearer $x|j}
      }
    };
    headers;
  };
  ApolloLinks.createContextLink(() => contextHandler(token));
};

/* Create an HTTP Link */
let httpLink =
  ApolloLinks.createHttpLink(~uri="http://localhost:4000/graphql", ());

/* WebSocket client */
let webSocketLink =
  ApolloLinks.webSocketLink(
    ~uri="ws://localhost:4000/graphql",
    ~reconnect=true,
    ()
  );

/* based on test, execute left or right */
let webSocketHttpLink =
  ApolloLinks.split(
    operation => {
      let operationDefition =
        ApolloUtilities.getMainDefinition(operation##query);
      operationDefition##kind == "OperationDefinition"
      && operationDefition##operation == "subscription";
    },
    webSocketLink,
    httpLink
  );

let getInstance = token =>
  ReasonApollo.createApolloClient(
    ~link=
      ApolloLinks.from([|
        headerContextLink(token),
        webSocketHttpLink,
        httpLink
      |]),
    ~cache=inMemoryCache,
    ()
  );