import React, { useEffect, useState, useCallback} from 'react';
import { GoogleMap, useJsApiLoader, Marker } from '@react-google-maps/api';

const containerStyle = {
    width : '100%',
    height: '600px'
};

const firstCenter = {
    lat: 10.784451,
    lng: 106.65754
}

const Map = () => {
    
    const { isLoaded } = useJsApiLoader({
        id: 'google-map-script',
        googleMapsApiKey: "AIzaSyAulKlJiaTuObt1Dbok2Cx23rpatT5ItCw"
    });

    const [map, setMap] = useState(null);
    const [center, setCenter] = useState({});
    const [data, setData] = useState([])

    useEffect(() => {
        fetch("http://localhost:9000/map")
        .then(res => res.json())
        .then(res => {
            setData([...res]);
            console.log(data);
        })
        .then(res => res.json())
        .then(res => {
            setCenter({
                lat: res.lat,
                lng: res.lng
            });
        })
        .catch(err => err);
    })

    const onLoad = useCallback(function callback(map) {
        const bounds = new window.google.maps.LatLngBounds(firstCenter);
        map.fitBounds(bounds);
        setMap(map)
    }, []);

    const onUnmount = useCallback(function callback(map) {
        setMap(null)
    }, []);

    return (isLoaded) ? ( <>
        <GoogleMap
            mapContainerStyle={containerStyle}
            center={center}
            defaultZoom={12}
            onLoad={onLoad}
            onUnmount={onUnmount}
            
        >
            { /* Child components, such as markers, info windows, etc. */}
        {/* {data.foreach((listData) => (

            listData.map((singleData, index) => {
                console.log(singleData);
                <Marker 
                    position = {{lat: .lat, lng: listData.lng}}
                />
            })
            
        ))} */}
        </GoogleMap></>) 
        : <></>
}

export default Map;