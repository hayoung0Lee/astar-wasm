import { useEffect, useState, useReducer } from "react"
import useReturnArraySlowly from "./useReturnArraySlowly";
import MapItem from "./MapItem"

const Map = ({ mapInstance, mapProps, route }) => {
    const [ignored, forceUpdate] = useReducer(x => x + 1, 0);

    const {
        width,
        height,
        rowCount,
        colCount
    } = mapProps;

    const [slowArr, initSlowArr, clearSlowArr] = useReturnArraySlowly(1000, {
        colCount: mapProps.colCount,
        rowCount: mapProps.rowCount,
    })

    const [routeArr, setRouteArr] = useState([]);

    const addObstacle = (e, a, b) => {
        mapInstance.addObstacle(a, b);
        forceUpdate(prev => prev + 1)
    }

    const removeObstacle = (e, a, b) => {
        if (e.detail === 2) {
            mapInstance.removeObstacle(a, b);
            forceUpdate(prev => prev + 1)
        }
    }

    useEffect(() => {
        if (route) {
            const newArr = Array.from(Array(route.size()).keys()).map((i) => route.get(i).id)
            setRouteArr(newArr)
            initSlowArr(newArr)
        } else {
            setRouteArr([])
            clearSlowArr()
        }
    }, [route])

    useEffect(() => {
        console.log("ignored", ignored)
    }, [])

    return <div style={{ width: width, height: height }}>
        {Array.from(Array(rowCount).keys()).map((i) => {
            return <div key={`height_${i}`} style={{
                display: "flex"
            }}>
                {Array.from(Array(colCount).keys()).map((j) => {
                    if (routeArr.length === 0) {
                        return <MapItem
                            key={`width_${j}`}
                            mapProps={mapProps}
                            style={{
                                backgroundColor: mapInstance.mapStatus(i, j) ? "black" : "#D3D3D3",
                            }}
                            onDoubleClick={(e) => removeObstacle(e, i, j)}
                            onClick={(e) => addObstacle(e, i, j)}

                        >
                            {i === 0 && j === 0 && "START"}
                            {i === rowCount - 1 && j === colCount - 1 && "GOAL"}
                            {!(i === 0 && j === 0) && !(i === rowCount - 1 && j === colCount - 1) && `(${i}, ${j})`}
                        </MapItem>
                    }

                    return <MapItem
                        key={`width_${j}`}
                        mapProps={mapProps}
                        style={{
                            border: slowArr[i][j] ? "3px solid black" : "1px solid black",
                            backgroundColor: mapInstance.mapStatus(i, j) ? "black" : (slowArr[i][j] ? "grey" : "#D3D3D3")
                        }}
                        onDoubleClick={(e) => removeObstacle(e, i, j)}
                        onClick={(e) => addObstacle(e, i, j)}
                    >
                        {i === 0 && j === 0 && "START"}
                        {i === rowCount - 1 && j === colCount - 1 && "GOAL"}
                    </MapItem>
                })}
            </div>
        })}
    </div >
}

export default Map