open SharedTypes;

type firebaseConfig = {
    .
    "apiKey": string,
    "databaseURL": string
};

type firebaseDatabase;
type firebaseReference;
type firebaseSnapshot;

let config =  [%bs.obj {
    "apiKey": " AIzaSyBi-KlDUGdM4SlTFJkKMlLi5qGPBWuABvU ",
    "databaseURL": "https://scrabble-e05f2.firebaseio.com/"
}];

[@bs.module "firebase/app"] external initializeApp: (firebaseConfig => unit) = "initializeApp";
[@bs.module "firebase"] external getDatabaseReference: ( unit => firebaseDatabase) = "database";
[@bs.send] external getFirebaseReference: (firebaseDatabase, string) => firebaseReference = "ref";
[@bs.send] external setStringValue: (firebaseReference, string) => Js.Promise.t(unit) = "set";
[@bs.send] external setOnListener: (firebaseReference, string, (firebaseSnapshot => unit)) => unit = "on";
[@bs.send] external turnOffListener: (firebaseReference) => unit = "off";
[@bs.send] external getSnapshotValue: (firebaseSnapshot) => string = "val";
[@bs.send] external deleteNode: firebaseReference => unit = "remove";

let startFirebase = () => {
    Js.log("Starting firebase");
    initializeApp(config);
};

let createGame: string => unit = gameId => {
    let database = getDatabaseReference();
    let gameReference = getFirebaseReference(database, gameId);
    deleteNode(gameReference);
    let reference = getFirebaseReference(database, gameId ++ "/playerOneStatus");
    let _ = setStringValue(reference, "joined");
};

let joinGame: string => unit = gameId => {
    let database = getDatabaseReference();
    let reference = getFirebaseReference(database, gameId ++ "/playerTwoStatus");
    let _ = setStringValue(reference, "joined")
};

let getMyDataPath: connection => string = connection => {
    let (gameId, playerId) = connection;
    gameId ++ "/" ++ playerId ++ "/" ++ "data"
}

let getOpponentsDataPath: connection => string = connection => {
    let (gameId, playerId) = connection;
    let playerId = switch (playerId) {
        | "1" => "2"
        | "2" => "1"
        | _ => "Error" // Won't happen
    };
    gameId ++ "/" ++ playerId ++ "/" ++ "data"
}

let putNewMove: (dataToSend, connection) => Js.Promise.t(unit) = (dataToSend, connection) => {
    let database = getDatabaseReference();
    let reference = getFirebaseReference(database, getMyDataPath(connection));
    let encoded = JsonEncodeDecode.Encode.dataToSendEncoder(dataToSend) |> Js.Json.stringify;
    setStringValue(reference, encoded);
}

let listenToMove: (connection, dataToSend => unit) => unit = (connection, callback) => {
    let database = getDatabaseReference();
    let reference = getFirebaseReference(database, getOpponentsDataPath(connection));
    setOnListener(reference, "value", (snapshot) => {
        let encodedString = snapshot |> getSnapshotValue;
        Js.log("Encoded data:")
        Js.log(encodedString)
        let parsedJson = encodedString |> Json.parse
        switch (parsedJson) {
            | Some(json) => {
                let data: dataToSend = JsonEncodeDecode.Decode.dataToSendDecoder(json)
                Js.log("Decoded data")
                Js.log(data)
                callback(data)
            }
            | None => ()
        }
    })
}

let stopListening: (connection) => unit = (connection) => {
    let database = getDatabaseReference();
    let reference = getFirebaseReference(database, getOpponentsDataPath(connection) ++ "/data");
    turnOffListener(reference);
}