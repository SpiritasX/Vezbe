<template>
<div>
    <h2 style="text-align:center">Employee Profile</h2>
    <div class="card">
        <img alt="User" src="../assets/user.png"/>
        <h1> {{ employee.firstName }} </h1>
        <h1> {{ employee.lastName }} </h1>
        <p class="title">{{employee.position}}</p>
        <br>
    </div>
</div>
</template>
<script>
//import axios from "axios";
export default {
    name: 'EmployeeView',
    data: function() {
        return {
            employee: {},
        }
    },
    mounted: function() {
        /*axios
            .get("http://localhost:8081/api/employees/" + this.$route.query.id)
            .then((res) => {
                this.employee = res.data
            })
            .catch((err) => {
                console.log(err)
            })*/

        fetch('http://localhost:8081/api/employees/' + this.$route.query.id)
            .then(response => response.json())
            .then(data => {console.log("Success:", data); this.employee = data})
            .catch((error) => {
                console.error("Error:", error);
            });
    }
}
</script>
