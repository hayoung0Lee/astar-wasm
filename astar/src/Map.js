import { useEffect, useState } from "react"


const Map = ({ map, mapSize, mapCount }) => {
    const [c, setC] = useState();
    const addObstacle = (a, b) => {
        c.addObstacle(a, b);
    }

    const removeObstacle = (a, b) => {
        c.removeObstacle(a, b);
    }

    useEffect(() => {
        setC(map)
    }, [])

    return <div style={{ margin: "30px auto", width: mapSize.width, height: mapSize.height }}>
        {Array.from(Array(mapCount.height).keys()).map((i) => {
            return <div key={i} style={{
                display: "flex"
            }}>
                {Array.from(Array(mapCount.width).keys()).map((j) => {
                    return <div key={j} style={{
                        width: `${mapSize.width / mapCount.width}px`,
                        height: `${mapSize.height / mapCount.height}px`,
                        border: "1px solid black",
                        display: "flex",
                        alignItems: "center",
                        justifyContent: "center"
                    }}>
                        {i === 0 && j === 0 && "START"}
                        {i === mapCount.height - 1 && j === mapCount.width - 1 && "GOAL"}
                    </div>
                })}
            </div>
        })}
    </div>
}

export default Map