import React, { useEffect } from 'react'
// import axios from 'axios';
import { Box, Button } from '@mui/material';
import Map from '../../components/Map/Map';

const Overview = () => {

    // const [data, setData] = useState([])

    useEffect(() => {
        fetch("http://localhost:9000/overview")
        .catch(err => err);
    })

    return (
        <>
        <Map />
        <Box sx={{
            display: 'grid',
            gridTemplateColumns: 'repeat(2, 1fr)',
            gap: 1,
            gridTemplateRows: 'auto',}} 
            style={{marginTop: 50, padding: "50px 20px"}}>
        {/*Chart of Velocity here*/}
        <Button variant="contained" style={{padding: "20px 50px"}}>Velocity:<br/> 60km/h</Button>

        <Button variant="contained" style={{padding: "20px 50px"}}>Acceleration:<br/> 3km/h^2</Button>
        </Box>
        </>
    )
    
}

export default Overview;