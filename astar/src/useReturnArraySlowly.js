/* eslint-disable no-undef */
import { useState, useEffect, useRef } from "react";

let intervalId;

const useReturnArraySlowly = (time, { rowCount, colCount }) => {
    const [initialRoute, setInitialRoute] = useState([])
    const [slowRoute, setSlowRoute] = useState([])
    const [timer, setTimer] = useState(1);
    const [slowArr, setSlowArr] = useState(Array(rowCount).fill(0).map(() => Array(colCount).fill(false)))

    useEffect(() => {
        if (initialRoute) {
            if (intervalId) {
                clearInterval(intervalId)
            }
            intervalId = setInterval(() => {
                setTimer(prev => {
                    return prev + 1
                })
            }, time)
        }
    }, [initialRoute, slowRoute])

    useEffect(() => {
        if (initialRoute) {
            if (slowRoute.length === initialRoute.length) {
                clearInterval(intervalId)
            } else {
                const newElem = initialRoute[slowRoute.length]
                setSlowRoute([...slowRoute, newElem])
                setSlowArr(slowArr.map((arr, pi) =>
                    arr.map((item, pj) => {
                        if (pi === newElem.x && pj === newElem.y) {
                            return true;
                        } else {
                            return item
                        }
                    })
                ))
            }
        }
    }, [timer])

    const initSlowArr = (routeArr) => {
        setSlowRoute([])
        setSlowArr(Array(rowCount).fill(0).map(() => Array(colCount).fill(false)))
        setInitialRoute(routeArr)
    }

    const clearSlowArr = () => {
        if (intervalId) {
            clearInterval(intervalId)
        }
        setSlowArr(Array(rowCount).fill(0).map(() => Array(colCount).fill(false)))
        setInitialRoute([])
        setSlowRoute([])
    }
    return [slowArr, initSlowArr, clearSlowArr]
}

export default useReturnArraySlowly;