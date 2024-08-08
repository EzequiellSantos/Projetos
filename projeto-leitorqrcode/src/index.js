
import { Html5Qrcode } from "html5-qrcode";

document.getElementById('startButton').addEventListener('click', function() {
    const html5QrCode = new Html5Qrcode("reader");

    function onScanSuccess(decodedText, decodedResult) {
        document.getElementById('qrResult').value = decodedText;
        html5QrCode.stop().then((ignore) => {
            // QR Code scanning is stopped.
        }).catch((err) => {
            console.error("Stop failed: ", err);
        });
    }

    function onScanFailure(error) {
        console.warn(`Code scan error = ${error}`);
    }

    html5QrCode.start(
        { facingMode: "environment" }, // Use rear camera
        {
            fps: 10,    // Optional, frame per seconds for qr code scanning
            qrbox: { width: 250, height: 250 }  // Optional, if you want bounded box UI
        },
        onScanSuccess,
        onScanFailure
    ).catch((err) => {
        console.error("Unable to start scanning: ", err);
    });
});
