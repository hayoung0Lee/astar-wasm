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
  const [route, setRoute] = useState()

  const [init, setInit] = useState(true)
  useEffect(() => {
    if (!loading && init) {
      const c = new modules.MapManager(width, height);
      setMapInstance(c)

      const m = c.getMap();

      const astar = new Module.AstarPathFinder(m);
      const result = astar.getResult(true);
      setRoute(result)
      setInit(false)
    }
  }, [loading])

  if (loading || !mapInstance || !route) {
    return <div>Loading wasm</div>
  }

  return (
    <div className="App">
      <Map route={route} map={mapInstance} mapSize={{ width: MAP_WIDTH, height: MAP_HEIGHT }} mapCount={{ width, height }} />
    </div>
  );
}

export default App;