import { useEffect, useState } from "react"
import useReturnArraySlowly from "./useReturnArraySlowly";
import MapItem from "./MapItem"

const Map = ({ mapInstance, mapProps, route }) => {
    const {
        width,
        height,
        rowCount,
        colCount
    } = mapProps;


    const [slowArr, initSlowArr] = useReturnArraySlowly(2000, {
        colCount: mapProps.colCount,
        rowCount: mapProps.rowCount,
    })

    const [routeArr, setRouteArr] = useState([]);

    const addObstacle = (e, a, b) => {
        mapInstance.addObstacle(a, b);
        console.log("add")
    }

    const removeObstacle = (e, a, b) => {
        if (e.detail === 2) {
            mapInstance.removeObstacle(a, b);
            console.log("Remove")
        }
    }

    useEffect(() => {
        if (route) {
            const newArr = Array.from(Array(route.size()).keys()).map((i) => route.get(i).id)
            setRouteArr(newArr)
            initSlowArr(newArr)
        }
    }, [route])

    useEffect(() => {
        // console.log("slowArr", slowArr)
    }, [slowArr])

    return <div style={{ margin: "30px auto", width: width, height: height }}>
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
                                backgroundColor: mapInstance.mapStatus(i, j) === 1 ? "black" : "#D3D3D3",
                            }}
                            onDoubleClick={(e) => removeObstacle(e, i, j)}
                            onClick={(e) => addObstacle(e, i, j)}
                        >
                            {i === 0 && j === 0 && "START"}
                            {i === rowCount - 1 && j === colCount - 1 && "GOAL"}
                        </MapItem>
                    }

                    return <MapItem
                        key={`width_${j}`}
                        mapProps={mapProps}
                        style={{
                            border: slowArr[i][j] ? "3px solid black" : "1px solid black",
                            backgroundColor: mapInstance.mapStatus(i, j) === 1 ? "black" : (slowArr[i][j] ? "grey" : "#D3D3D3")
                        }}
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