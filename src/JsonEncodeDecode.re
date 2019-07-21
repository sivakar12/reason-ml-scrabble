open SharedTypes;
module Encode = {
    let tileEncoder = (tile: tile) => {
        Json.Encode.(
            object_([
                ("letter", tile.letter |> char),
                ("value", tile.value |> int)
            ])
        )
    }

    let newPlacementsEncoder = (newPlacements: newPlacements) => {
        Json.Encode.(
            newPlacements |> list(tuple3(tileEncoder, int, int))
        )
    }

    let bagRemovalsEncoder = (bagRemovals: bagRemovals) => {
        Json.Encode.(
            bagRemovals |> list(tileEncoder)
        )
    }

    let dataToSendEncoder = (dataToSend: dataToSend) => {
        Json.Encode.(
            dataToSend |> tuple2(newPlacementsEncoder, bagRemovalsEncoder)
        )
    }
}

module Decode = {
    let tileDecoder = json => Json.Decode.{
        letter: json |> field("letter", char),
        value: json |> field("value", int)
    }

    let newPlacementsDecoder = json => Json.Decode.(
        json |> array(tuple3(tileDecoder, int, int)) |> Belt.List.fromArray
    )

    let bagRemovalsDecoder = json => Json.Decode.(
        json |> array(tileDecoder) |> Belt.List.fromArray
    )

    let dataToSendDecoder = json => Json.Decode.(
        json |> tuple2(newPlacementsDecoder, bagRemovalsDecoder)
    )
}