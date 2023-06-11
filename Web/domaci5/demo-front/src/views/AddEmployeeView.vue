<template>
  <label for="firstName">First name:</label>
  <input v-model="employee.firstName" /><br />
  <label for="lastName">Last name:</label>
  <input v-model="employee.lastName" /><br />
  <label for="position">Position:</label>
  <input v-model="employee.position" /><br />
  <button v-on:click="submit()">submit</button>
</template>

<script>
import axios from "axios"
export default {
  name: "AddEmployeeView",
  data: function () {
    return {
      employee: {
        firstName: "",
        lastName: "",
        position: "",
      },
    };
  },
  methods: {
    submit: function () {

      axios
        .post("http://localhost:8081/api/employees", this.employee)
        .then((res) => {
          console.log(res);
          this.$router.push("/employees");
        })
        .catch((err) => {
          console.log(err);
          alert("Something went wrong!");
        });

      /*fetch("http://localhost:8081/api/employees", {
        method: "POST",
        headers: {
          Accept: "application/json",
          "Content-type": "application/json",
        },
        body: JSON.stringify(this.employee),
      })
        .then((response) => response.json)
        .then((data) => {
          console.log("Success : " + data);
          this.$router.push("/employees");
        })
        .catch((err) => {
          console.log("Error : " + err);
          alert(err);
        });*/
    },
  },
};
</script>
