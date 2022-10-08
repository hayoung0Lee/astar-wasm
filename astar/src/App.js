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


      c.addObstacle(0, 5)
      c.addObstacle(4, 9)
      c.addObstacle(4, 8)
      c.addObstacle(4, 4)
      c.addObstacle(4, 5)
      c.addObstacle(2, 4);
      c.addObstacle(4, 3);
      c.addObstacle(3, 4);
      c.addObstacle(1, 2);

      const m = c.getMap();

      const astar = new Module.AstarPathFinder(m);
      const result = astar.getResult(false);
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
