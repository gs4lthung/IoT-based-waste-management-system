async function check() {
    try {
        const data = await getBlynkInfo();
        const tmp = data;
        alert(data); // Assuming 'data' is the value you want to display
        displayNotFull_Full(tmp);
    } catch (error) {
        console.error('Error in check function:', error);
    }
    // getBlynkInfo().then(level => {
    //     alert("Bin level: " + level); 
    //     displayNotFull_Full(level);  
    // }).catch(error => {
    //     console.error('Error:', error);
    // });
}

function displayNotFull_Full(tmp) {
    const binFull = document.querySelector('.Bin_full');
    const binNotFull = document.querySelector('.Bin_Notfull');

    if (tmp > 80) {
        binFull.style.display = 'block';
        binNotFull.style.display = 'none';
    } else {
        binFull.style.display = 'none';
        binNotFull.style.display = 'block';
    }
}

async function getBlynkInfo() {
    const BLYNK_SERVER = 'https://blynk.cloud/external/api/get?token=BvH3H3framvDOR6LVOmWDs9oAELIIZ9D&dataStreamId=4';
    try {
        const response = await fetch(BLYNK_SERVER);
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }
        const data = await response.json();
        console.log(data);
        return data; // assuming 'data' is the numeric bin level
    } catch (error) {
        console.error('There has been a problem with your fetch operation:', error);
        throw error;
    }
}
/*
async function check() {
    try {
        const data = await getBlynkInfo();
        alert(data); // Assuming 'data' is the value you want to display
    } catch (error) {
        console.error('Error in check function:', error);
    }
}*/
/*
async function getBlynkInfo() {
    const BLYNK_SERVER = 'https://blynk.cloud/external/api/get?token=BvH3H3framvDOR6LVOmWDs9oAELIIZ9D&dataStreamId=4';

    try {
        const response = await fetch(BLYNK_SERVER);
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }
        const data = await response.json();
        console.log(data);
        return data; // Return the data for use in 'check'
    } catch (error) {
        console.error('There has been a problem with your fetch operation:', error);
        throw error; // Re-throw the error to be caught in 'check'
    }
}
*/
/**
 * function check() {
    getBlynkInfo('v2'); 
}

function displayNotFull_Full() {
    
}

function getBlynkInfo(PIN_ID) {
    const BLYNK_SERVER = 'blynk.cloud'
    const BLYNK_AUTH_TOKEN = 'BvH3H3framvDOR6LVOmWDs9oAELIIZ9D'; 
    const requestURL = `${BLYNK_SERVER}/${BLYNK_AUTH_TOKEN}/get/${PIN_ID}`;

    fetch(requestURL)
        .then(response => {
            if (!response.ok) {
                throw new Error('Network response was not ok');
            }
            return response.json();
        })
        .then(data => {
            console.log('Received data from Blynk:', data);
            if (data && data.length > 0) {
                let v2Value = data[0]; 
                alert(`The value of V2 is: ${v2Value}`);
                if (v2Value > 80) {
                    alert('THE BIN IS FULL!!!!'); 
                } else {
                    alert('THE BIN IS NOT FULL!!!!');
                }
            }
        })

 */