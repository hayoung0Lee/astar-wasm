import { useEffect, useState } from "react"
import useReturnArraySlowly from "./useReturnArraySlowly";


const Map = ({ map, mapSize, mapCount, route }) => {
    const [c, setC] = useState();
    const [slowArr] = useReturnArraySlowly(route, 1000, mapCount)

    const addObstacle = (e, a, b) => {
        if (e.detail === 1) {
            c.addObstacle(a, b);
            console.log("add")
        }
    }

    const removeObstacle = (e, a, b) => {

        c.removeObstacle(a, b);

        console.log("Remove")
    }


    useEffect(() => {
        setC(map)
    }, [])

    useEffect(() => {
        // console.log("slowArr", slowArr)
    }, [slowArr])

    return <div style={{ margin: "30px auto", width: mapSize.width, height: mapSize.height }}>
        {Array.from(Array(mapCount.height).keys()).map((i) => {
            return <div key={`height_${i}`} style={{
                display: "flex"
            }}>
                {Array.from(Array(mapCount.width).keys()).map((j) => {
                    return <div key={`width_${j}`} style={{
                        width: `${mapSize.width / mapCount.width}px`,
                        height: `${mapSize.height / mapCount.height}px`,
                        display: "flex",
                        alignItems: "center",
                        justifyContent: "center",
                        border: slowArr[i][j] ? "3px solid black" : "1px solid black",
                        backgroundColor: slowArr[i][j] ? "grey" : "#D3D3D3"

                    }}
                        onDoubleClick={(e) => removeObstacle(e, i, j)}
                        onClick={(e) => addObstacle(e, i, j)}
                    >
                        {i === 0 && j === 0 && "START"}
                        {i === mapCount.height - 1 && j === mapCount.width - 1 && "GOAL"}
                    </div>
                })}
            </div>
        })}
    </div>
}

export default Map