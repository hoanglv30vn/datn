
const firebaseConfig = {
    apiKey: "AIzaSyAEqi81NFMPBJGxWRy7QtQv961efPzL9LA",
    authDomain: "hellodatn.firebaseapp.com",
    databaseURL: "https://hellodatn-default-rtdb.asia-southeast1.firebasedatabase.app",
    projectId: "hellodatn",
    storageBucket: "hellodatn.appspot.com",
    messagingSenderId: "559705579450",
    appId: "1:559705579450:web:3421e5377912259256c783",
    measurementId: "G-YK901S5FXQ"
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
const analytics = getAnalytics(app);