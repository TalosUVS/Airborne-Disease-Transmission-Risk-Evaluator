#ifndef UUID1281974329968
#define UUID1281974329968

/**
  * DecisionTreeClassifier(ccp_alpha=0.0, class_name=DecisionTreeClassifier, class_weight=None, criterion=gini, max_depth=None, max_features=None, max_leaf_nodes=None, min_impurity_decrease=0.0, min_samples_leaf=1, min_samples_split=2, min_weight_fraction_leaf=0.0, monotonic_cst=None, num_outputs=2, package_name=everywhereml.sklearn.tree, random_state=42, splitter=best, template_folder=everywhereml/sklearn/tree)
 */
class DecisionTreeClassifier {
    public:

        /**
         * Predict class from features
         */
        int predict(float *x) {
            int predictedValue = 0;
            size_t startedAt = micros();

            
                    
            
            if (x[3] < 11.5) {
                
                    
            if (x[4] < 26.752887725830078) {
                
                    
            if (x[3] < 5.5) {
                
                    
            if (x[1] < 35.170650482177734) {
                
                    
            if (x[4] < 20.974677085876465) {
                
                    
            predictedValue = 0;

                
            }
            else {
                
                    
            predictedValue = 1;

                
            }

                
            }
            else {
                
                    
            predictedValue = 0;

                
            }

                
            }
            else {
                
                    
            if (x[2] < 491.5) {
                
                    
            predictedValue = 0;

                
            }
            else {
                
                    
            if (x[4] < 24.522130012512207) {
                
                    
            predictedValue = 1;

                
            }
            else {
                
                    
            if (x[4] < 25.83340358734131) {
                
                    
            predictedValue = 0;

                
            }
            else {
                
                    
            predictedValue = 1;

                
            }

                
            }

                
            }

                
            }

                
            }
            else {
                
                    
            if (x[0] < 18.572924613952637) {
                
                    
            if (x[0] < 18.363314628601074) {
                
                    
            predictedValue = 0;

                
            }
            else {
                
                    
            predictedValue = 1;

                
            }

                
            }
            else {
                
                    
            if (x[0] < 19.65934467315674) {
                
                    
            if (x[1] < 40.22640419006348) {
                
                    
            predictedValue = 1;

                
            }
            else {
                
                    
            predictedValue = 0;

                
            }

                
            }
            else {
                
                    
            predictedValue = 0;

                
            }

                
            }

                
            }

                
            }
            else {
                
                    
            if (x[3] < 18.5) {
                
                    
            if (x[4] < 39.24576950073242) {
                
                    
            if (x[0] < 18.56305694580078) {
                
                    
            if (x[1] < 45.13727569580078) {
                
                    
            predictedValue = 1;

                
            }
            else {
                
                    
            predictedValue = 0;

                
            }

                
            }
            else {
                
                    
            predictedValue = 1;

                
            }

                
            }
            else {
                
                    
            if (x[3] < 16.5) {
                
                    
            predictedValue = 0;

                
            }
            else {
                
                    
            if (x[4] < 43.315147399902344) {
                
                    
            predictedValue = 1;

                
            }
            else {
                
                    
            if (x[2] < 694.0) {
                
                    
            predictedValue = 0;

                
            }
            else {
                
                    
            predictedValue = 1;

                
            }

                
            }

                
            }

                
            }

                
            }
            else {
                
                    
            predictedValue = 1;

                
            }

                
            }


                    

            latency = micros() - startedAt;

            return (lastPrediction = predictedValue);
        }

        
            
            /**
             * Get latency in micros
             */
            uint32_t latencyInMicros() {
                return latency;
            }

            /**
             * Get latency in millis
             */
            uint16_t latencyInMillis() {
                return latency / 1000;
            }
            

    protected:
        float latency = 0;
        int lastPrediction = 0;

        
            
            
};



static DecisionTreeClassifier riskClassifier;


#endif