package com.lorworwag.food_barcode_scanner;

import java.util.ArrayList;
import java.util.HashMap;

public class BarcodeDataTemplate {
    private String id;
    private ArrayList<String> ingredients;
    private HashMap<String, String> nutritionFacts;
    private String productName;

    public BarcodeDataTemplate() {
    }

    public BarcodeDataTemplate(String id, ArrayList<String> ingredients, HashMap<String, String> nutritionFacts, String productName) {
        this.id = id;
        this.ingredients = ingredients;
        this.nutritionFacts = nutritionFacts;
        this.productName = productName;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public ArrayList<String> getIngredients() {
        return ingredients;
    }

    public void setIngredients(ArrayList<String> ingredients) {
        this.ingredients = ingredients;
    }

    public HashMap<String, String> getNutritionFacts() {
        return nutritionFacts;
    }

    public void setNutritionFacts(HashMap<String, String> nutritionFacts) {
        this.nutritionFacts = nutritionFacts;
    }

    public String getProductName() {
        return productName;
    }

    public void setProductName(String productName) {
        this.productName = productName;
    }
}
