/* eslint-disable no-undef */
import './App.css';
import React, { useEffect, useState } from "react"
import useLoadWasmModule from './useLoadWasm';
import Map from './Map';


const MAP_WIDTH = 800
const MAP_HEIGHT = 700


function App() {
  const [loading, modules] = useLoadWasmModule(`${process.env.PUBLIC_URL}/static/js/main.js`, ["MapManager", "AstarPathFinder"])
  const [mapInstance, setMapInstance] = useState()
  const [rowCount, setRowCount] = useState(10)
  const [colCount, setColCount] = useState(10)
  const [route, setRoute] = useState()

  useEffect(() => {
    if (!loading) {
      setMapInstance(new modules.MapManager(colCount, rowCount))
    }
  }, [loading])

  const handleRoute = () => {
    const m = mapInstance.getMap();
    const astar = new modules.AstarPathFinder(m);
    const result = astar.getResult(true);
    setRoute(result)
  }

  const clearRoute = () => {
    setRoute()
  }

  if (loading || !mapInstance) {
    return <div>Loading wasm</div>
  }

  return (
    <div className="App" style={{ display: "flex", flexDirection: "column", alignItems: "center", paddingTop: 20 }}>
      <Map
        mapInstance={mapInstance}
        mapProps={{
          width: MAP_WIDTH,
          height: MAP_HEIGHT,
          rowCount: rowCount,
          colCount: colCount
        }}
        route={route}
      />
      <div style={{
        display: "flex",
        gap: 20,
        marginTop: 10
      }}>
        <button style={{
          width: 100,
          height: 70
        }}
          onClick={handleRoute}
        >
          Start
        </button>
        <button style={{
          width: 100,
          height: 70
        }}
          onClick={clearRoute}
        >
          Clear
        </button>
      </div>
    </div>
  );
}

export default App;
