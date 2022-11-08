import React, { useState } from "react";
import {
    AppBar,
    Toolbar,
    Avatar,
    Box,
    Divider,
    IconButton,
    List,
    ListItem,
    ListItemIcon,
    ListItemText,
    CssBaseline,
    Drawer,
    Typography,
} from "@mui/material"
import {
    // Apps,
    Menu,
    // ContactMail,
    AssignmentInd, 
    Home
} from "@mui/icons-material"
import {
    makeStyles
} from 'tss-react/mui';
import { useNavigate } from "react-router-dom";

const useStyles = makeStyles()((theme) => {
    return {
        menuSliderContainer: {
            width: 250,
            background: '#3f51b5',
            height: "100%"
        },
        avatar: {
            margin: "0.5rem auto",
            padding: "1rem",
            width: theme.spacing(13),
            height: theme.spacing(13),
        },
        listItem: {
            color: "white"
        }
    }
});

const listItems = [
    {
        listIcon: <Home />,
        listText: "Overview"
    },
    {
        listIcon: <AssignmentInd />,
        listText: "Blackbox Management"
    }
]

const Sidebar = () => {
    const classes = useStyles();
    const [open, setOpen] = useState(false);
    const navigate = useNavigate();

    const toggleSlider = () => {
        setOpen(!open);
    };

    const onAvatarClick = () => {
        navigate("/");
    }

    const handleItemClick = (item) => {
        if(item.listText === "Overview") navigate("/overview");

        else return navigate("/management")
    }

    const sideList = () => (
        <Box className={classes.menuSliderContainer} component="div">
            <Avatar
                className={classes.avatar}
                src="https://i.ibb.co/rx5DFbs/avatar.png"
                alt="Juaneme8"
                onClick = {() => onAvatarClick()}
            />
            <Divider />
            <List>
                {listItems.map((listItem, index) => (
                <ListItem className={classes.listItem} button key={index} onClick={() => handleItemClick(listItem)}>
                    <ListItemIcon className={classes.listItem}>
                    {listItem.listIcon}
                    </ListItemIcon>
                    <ListItemText primary={listItem.listText} />
                </ListItem>
                ))}
            </List>
        </Box>
    );
    
    return (
        <>
            <CssBaseline />
            <Box component="nav">
            <AppBar position="static">
                <Toolbar>
                <IconButton onClick={toggleSlider}>
                    <Menu />
                </IconButton>
                <Typography>Portfolio</Typography>
                <Drawer open={open} anchor="left" onClose={toggleSlider}>
                    {sideList()}
                </Drawer>
                </Toolbar>
            </AppBar>
            </Box>
        </>
    );
}

export default Sidebar;