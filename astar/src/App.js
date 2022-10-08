/* eslint-disable no-undef */
import './App.css';
import React, { useEffect, useState } from "react"
import useLoadWasmModule from './useLoadWasm';
import Map from './Map';


const MAP_WIDTH = 800
const MAP_HEIGHT = 750


function App() {
  const [loading, modules] = useLoadWasmModule(`${process.env.PUBLIC_URL}/static/js/main.js`, ["MapManager", "AstarPathFinder"])
  const [mapInstance, setMapInstance] = useState()
  const [width, setWidth] = useState(10)
  const [height, setHeight] = useState(10)

  useEffect(() => {
    if (!loading) {
      const c = new modules.MapManager(width, height);
      setMapInstance(c)
    }
  }, [loading])

  if (loading) {
    return <div>Loading wasm</div>
  }

  return (
    <div className="App">
      <Map map={mapInstance} mapSize={{ width: MAP_WIDTH, height: MAP_HEIGHT }} mapCount={{ width, height }} />
    </div>
  );
}

export default App;
