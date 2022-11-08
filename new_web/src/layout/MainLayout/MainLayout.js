import React, {useEffect} from "react";
import { Outlet } from "react-router-dom";

const MainLayout = () => {

    useEffect(() => {
        fetch("http://localhost:9000")
        .catch(err => err);
    })

    return(
        <div>
            <h1>Main Layout</h1>
            <Outlet />
        </div>
    )

};

export default MainLayout;