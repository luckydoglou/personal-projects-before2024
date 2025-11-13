package com.lorworwag.food_barcode_scanner;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.GridLayoutManager;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;
import com.google.zxing.integration.android.IntentIntegrator;
import com.google.zxing.integration.android.IntentResult;

public class HomeActivity extends AppCompatActivity {

    private static final String TAG = "HomeActivity";

    private Button btnScanBarcode;
    private TextView txtBarcode;
    private RecyclerView recyclerViewIngredients;
    private TextView txtIngredients;
    private RecyclerView recyclerViewNutritionFacts;
    private TextView txtNutritionFacts;
    private TextView txtProductName;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_home);

        btnScanBarcode = findViewById(R.id.btnScanBarcode);
        txtBarcode = findViewById(R.id.txtBarcode);
        recyclerViewIngredients = findViewById(R.id.recyclerViewIngredients);
        txtIngredients = findViewById(R.id.txtIngredients);
        recyclerViewNutritionFacts = findViewById(R.id.recyclerViewNutritionFacts);
        txtNutritionFacts = findViewById(R.id.txtNutritionFacts);
        txtProductName = findViewById(R.id.txtProductName);

        txtBarcode.setVisibility(View.INVISIBLE);
        txtIngredients.setVisibility(View.INVISIBLE);
        txtNutritionFacts.setVisibility(View.INVISIBLE);
        txtProductName.setVisibility(View.INVISIBLE);

        btnScanBarcode.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                scanBarcode(v);
            }
        });
    }

    // ===================================================================================
    // Create the menu and add Settings to menu.
    // ===================================================================================
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.main_menu, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.settings:
                Intent intent = new Intent(HomeActivity.this, SettingsActivity.class);
                startActivity(intent);
                break;
            default:
                break;
        }
        return true;
    }

    @Override
    public void onResume() {
        super.onResume();
    }

    @Override
    public void onPause() {
        super.onPause();
    }

    // ===================================================================================
    // Bring up the camera and scan barcode.
    // ===================================================================================
    public void scanBarcode(View view) {
        IntentIntegrator intentIntegrator = new IntentIntegrator(HomeActivity.this);
        intentIntegrator.setPrompt("For flash use volume up key");
        intentIntegrator.setBeepEnabled(true);
        intentIntegrator.setOrientationLocked(true);
        intentIntegrator.setCaptureActivity(Capture.class);
        intentIntegrator.initiateScan();
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        IntentResult intentResult = IntentIntegrator.parseActivityResult(requestCode, resultCode, data);

        if (intentResult.getContents() != null) {
            fetchData(intentResult.getContents());
        } else {
            Toast.makeText(getApplicationContext(), "OOPS... You did not scan anything", Toast.LENGTH_LONG).show();
        }
    }

    // ===================================================================================
    // Fetch data from Firebase Real-Time database and populate the data to screen.
    // ===================================================================================
    private void fetchData(String barcode) {
        FirebaseDatabase database = FirebaseDatabase.getInstance();
        DatabaseReference myRef = database.getReference("barcodes").child(barcode);

        // Read from the database
        myRef.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                // This method is called once with the initial value and again
                // whenever data at this location is updated.
                BarcodeDataTemplate data = dataSnapshot.getValue(BarcodeDataTemplate.class);

                txtProductName.setText(data.getProductName());
                txtProductName.setVisibility(View.VISIBLE);

                txtBarcode.setText("Barcode No.: " + barcode);
                txtBarcode.setVisibility(View.VISIBLE);

                txtIngredients.setVisibility(View.VISIBLE);
                IngredientsRecyclerViewAdapter adapter = new IngredientsRecyclerViewAdapter();
                adapter.setIngredients(data.getIngredients());
                recyclerViewIngredients.setAdapter(adapter);
                recyclerViewIngredients.setLayoutManager(new GridLayoutManager(HomeActivity.this, 2));

                txtNutritionFacts.setVisibility(View.VISIBLE);
                NutritionFactsRecyclerViewAdapter nutritionFactsAdapter = new NutritionFactsRecyclerViewAdapter();
                nutritionFactsAdapter.setNutritionFacts(data.getNutritionFacts());
                recyclerViewNutritionFacts.setAdapter(nutritionFactsAdapter);
                recyclerViewNutritionFacts.setLayoutManager(new LinearLayoutManager(HomeActivity.this));
            }

            @Override
            public void onCancelled(DatabaseError error) {
                // Failed to read value
                Toast.makeText(HomeActivity.this, "OOPS... You did not scan anything", Toast.LENGTH_LONG).show();
            }
        });
    }

}
