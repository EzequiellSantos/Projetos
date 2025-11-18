import { Html5QrcodeScanner } from "html5-qrcode";

document.getElementById('startButton').addEventListener('click', function() {
    const qrCodeSuccessCallback = (decodedText, decodedResult) => {
        document.getElementById('qrResult').value = decodedText;
        console.log("Lido :))")
        document.getElementById("codeSaved").innerHTML += ` code:${decodedText} `
    };

    const qrCodeErrorCallback = (errorMessage) => {
        console.warn(`QR Code scan error: ${errorMessage}`);
    };

    const config = { 
        fps: 1, 
        qrbox: { width: window.innerWidth / 100 * 40, height: 150 },
        experimentalFeatures: {
            useBarCodeDetectorIfSupported: true
        },
        rememberLastUsedCamera: true
    };

    const html5QrcodeScanner = new Html5QrcodeScanner(
        "reader", config, false);

    html5QrcodeScanner.render(qrCodeSuccessCallback, qrCodeErrorCallback);
});
