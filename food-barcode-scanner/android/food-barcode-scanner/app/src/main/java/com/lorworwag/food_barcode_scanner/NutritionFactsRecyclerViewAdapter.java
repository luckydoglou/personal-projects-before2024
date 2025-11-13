package com.lorworwag.food_barcode_scanner;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

public class NutritionFactsRecyclerViewAdapter extends RecyclerView.Adapter<NutritionFactsRecyclerViewAdapter.ViewHolder> {

    private ArrayList<String> nutritionFacts = new ArrayList<>();

    public NutritionFactsRecyclerViewAdapter() {
    }

    @NonNull
    @Override
    public ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.nutrition_fact_item, parent, false);
        NutritionFactsRecyclerViewAdapter.ViewHolder holder = new NutritionFactsRecyclerViewAdapter.ViewHolder(view);
        return holder;
    }

    @Override
    public void onBindViewHolder(@NonNull ViewHolder holder, int position) {
        holder.txtNutritionFactItem.setText(nutritionFacts.get(position));
    }

    @Override
    public int getItemCount() {
        return nutritionFacts.size();
    }

    public ArrayList<String> getNutritionFacts() {
        return nutritionFacts;
    }

    public void setNutritionFacts(HashMap<String, String> nutritionFactsHM) {
        // convert HashMap items to ArrayList
        Iterator iterator = nutritionFactsHM.entrySet().iterator();
        while (iterator.hasNext()) {
            String str = "";
            Map.Entry element = (Map.Entry) iterator.next();
            str += element.getKey() + ": " + element.getValue();
            nutritionFacts.add(str);
        }
    }

    public class ViewHolder extends RecyclerView.ViewHolder {
        private TextView txtNutritionFactItem;

        public ViewHolder(@NonNull View itemView) {
            super(itemView);
            txtNutritionFactItem = itemView.findViewById(R.id.txtNutritionFactItem);
        }
    }

}
