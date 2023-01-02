/* eslint-disable no-undef */
import { useState, useEffect } from "react";
import useScript from "./useScript"

window.Module = {}

const useLoadWasmModule = (src, modules) => {
    const [_status] = useScript(src)
    const [loading, setLoading] = useState(true)
    const [wasmModule, setWasmModule] = useState({})

    useEffect(() => {
        Module.onRuntimeInitialized = _ => {
            setWasmModule(Module)
            setLoading(false)
        }
    }, [])

    return [loading, wasmModule]
}

export default useLoadWasmModule;