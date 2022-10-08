/* eslint-disable no-undef */
import { useState, useEffect, useRef } from "react";

let intervalId;
let count = 0;

const useReturnArraySlowly = (arr, time, mapCount) => {
    const [original] = useState(arr)
    const [newArr, setNewArr] = useState([])
    const countRef = useRef(1);
    const [timer, setTimer] = useState(1);
    const [mem, setMem] = useState(Array(mapCount.height).fill(0).map(() => Array(mapCount.width).fill(false)))

    useEffect(() => {
        intervalId = setInterval(() => {
            setTimer(prev => {
                countRef.current = prev + 1
                return countRef.current
            })
        }, time)
    }, [])

    useEffect(() => {
        if (newArr.length === original.size()) {
            clearInterval(intervalId)
        } else {
            const { x, y } = original.get(newArr.length).id
            console.log(x, y)
            setNewArr(prev => [...prev, original.get(prev.length)])
            setMem(prev => prev.map((arr, pi) =>
                arr.map((item, pj) => {
                    if (pi === x && pj === y) {
                        return true;
                    } else {
                        return item
                    }
                })
            ))
        }
    }, [timer])

    return [mem]
}

export default useReturnArraySlowly;