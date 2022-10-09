const MapItem = ({ mapProps, style, props, children }) => {
    return <div style={{
        width: `${mapProps.width / mapProps.colCount}px`,
        height: `${mapProps.height / mapProps.rowCount}px`,
        display: "flex",
        alignItems: "center",
        justifyContent: "center",
        border: "1px solid black",
        backgroundColor: "#D3D3D3",
        ...style
    }}
        {...props}
    >
        {children}
    </div>
}

export default MapItem