import { Html5QrcodeScanner } from "html5-qrcode";

document.getElementById('startButton').addEventListener('click', function() {
    const qrCodeSuccessCallback = (decodedText, decodedResult) => {
        document.getElementById('qrResult').value = decodedText;
    };

    const qrCodeErrorCallback = (errorMessage) => {
        console.warn(`QR Code scan error: ${errorMessage}`);
    };

    const config = { 
        fps: 10, 
        qrbox: { width: 250, height: 250 },
        experimentalFeatures: {
            useBarCodeDetectorIfSupported: true
        },
        rememberLastUsedCamera: true
    };

    const html5QrcodeScanner = new Html5QrcodeScanner(
        "reader", config, false);

    html5QrcodeScanner.render(qrCodeSuccessCallback, qrCodeErrorCallback);
});
