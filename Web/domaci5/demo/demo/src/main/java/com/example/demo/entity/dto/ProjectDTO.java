package com.example.demo.entity.dto;

import com.example.demo.entity.Employee;

import java.util.List;

public class ProjectDTO {
    private String name;
    private String url;
    private String projId;
    private List<Employee> employeeList;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getUrl() {
        return url;
    }

    public void setUrl(String url) {
        this.url = url;
    }

    public String getProjId() {
        return projId;
    }

    public void setProjId(String projId) {
        this.projId = projId;
    }
}
