// file: parking_fees.c
// description: processes parking actions
// @author Ryan Nowak rcn8263

#include <stdio.h>
#include <stdlib.h>

#define MAXIMUM_FEE         10.0    /// maximum dollar charge per day
#define MINIMUM_FEE         2.0     /// minimum dollars for <= 3 hours
#define FRACTIONAL_RATE     0.50    /// 50c per hour over 3
#define MINUTES_PER_HOUR    60.0    /// how many minutes in 1 hour
#define MAX_INPUT           80      /// maximum line length to read stdin

/// compute_charges calculates and returns dollars charged for minutes
///
/// @param minutes integer number of minutes parked
/// @return dollars amount to charge
double compute_charges(int minutes) {
    int hours = minutes / MINUTES_PER_HOUR;
    double dollars = MINIMUM_FEE + (FRACTIONAL_RATE * (hours-2));
    if (hours < 3) {
        return MINIMUM_FEE;
    }
    else if (dollars >= MAXIMUM_FEE){
        return MAXIMUM_FEE;
    }
    else {
        return dollars;
    }
}

/// main prompts for minutes parked, calculates charges, and prints 
/// a bill for each car's parking fee. When the user terminates the 
/// program (e.g. enters 0 to quit), the program prints the total 
/// number of cars parked, accumulated hours parked, and accumulated 
/// dollars charged.
///
/// @return status_code EXIT_SUCCESS or EXIT_FAILURE
int main (void) {
    int cars_processed = 0;
    double total_hours = 0;
    double total_fees = 0;
    int current_car = 0;
    int minutes_parked = 0;
    double hours_parked = 0;
    double current_fee = 0;
    char user[MAX_INPUT];

    for (;;) {
        current_car++;

        printf("Car %d: Enter minutes parked (control-d or 0 to quit): ", current_car);

        // gets user input
        fgets(user, MAX_INPUT, stdin);
        minutes_parked = strtol(user, NULL, 10);
        hours_parked = minutes_parked / MINUTES_PER_HOUR;

        // user chooses to quit program
        if (minutes_parked == 0) {
            break;
        }

        cars_processed++;
        total_hours += hours_parked;
        current_fee = compute_charges(minutes_parked);
        total_fees += current_fee;

        // prints the data of the car that was just processed
        printf("\nCar\tHours\tCharges\n");
        printf("%d\t%.2f\t$%.2f\n", current_car, hours_parked, current_fee);
    }

    // prints accumulated data
    printf("Cars Processed: %d\n", cars_processed);
    printf("Total Hours Parked: %.2f\n", total_hours);
    printf("Total Dollars Charged: $%.2f\n", total_fees);

    return 0;
}
