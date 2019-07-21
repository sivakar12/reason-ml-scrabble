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