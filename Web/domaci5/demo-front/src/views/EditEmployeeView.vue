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
name: "EditEmployeeView",
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
    submit() {
      axios
        .put(`http://localhost:8081/api/employees/${this.$route.query.id}`, this.employee)
        .then((res) => {
          console.log(res);
          this.$router.push("/employees");
        })
        .catch((err) => {
          console.log(err);
          alert("Something went wrong!");
        });
    },
    fetchEmployee() {
      axios
        .get(`http://localhost:8081/api/employees/${this.$route.query.id}`)
        .then((res) => {
          this.employee = res.data;
        })
        .catch((err) => {
          console.log(err);
          alert("Failed to fetch employee data!");
        });
    },
  },
  created() {
    this.fetchEmployee();
  },
};
</script>