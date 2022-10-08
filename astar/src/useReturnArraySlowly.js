/* eslint-disable no-undef */
import { useState, useEffect, useRef } from "react";

let intervalId;
let count = 0;

const useReturnArraySlowly = (arr, time, mapCount) => {
    const [original] = useState(Array.from(Array(arr.size()).keys()).map((i) => arr.get(i).id))
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
        if (newArr.length === original.length) {
            clearInterval(intervalId)
        } else {
            const newElem = original[newArr.length]

            setNewArr([...newArr, newElem])

            setMem(mem.map((arr, pi) =>
                arr.map((item, pj) => {
                    if (pi === newElem.x && pj === newElem.y) {
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