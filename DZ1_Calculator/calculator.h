#pragma once

#include <string>
#include <optional>
#include <cmath>
#include "enums.h"

using Error = std::string;

class Calculator{

public:
    Calculator(){}
    //~Calculator<Number>();

    double GetNumber()const{
        return accumulator_number_;
    }

    std::optional<double> GetMemoryNumber()const{
        return memory_number_;
    }

    void Save(){
        memory_number_=accumulator_number_;
    }

    void Load(){
        accumulator_number_ = memory_number_.value_or(0);
    }

    std::optional<double> GetHasMem()const{
        return std::optional(memory_number_);
    }

    std::optional<double> ResetMemoryNumber(){
        memory_number_ = std::nullopt;
        return std::nullopt;
    }

    void Set(double acc_num){
        accumulator_number_ = acc_num;
    }

    std::optional<Error> Add(double in_num){

        accumulator_number_ += in_num;

        return std::nullopt;
    }

    std::optional<Error> Sub(double in_num){

        accumulator_number_ -= in_num;

        return std::nullopt;
    }

    std::optional<Error> Mul(double in_num){

        accumulator_number_ *= in_num;

        return std::nullopt;
    }

    std::optional<Error> Div(double in_num){

        if (in_num == 0){
            return std::optional("Division by zero");
        }
        accumulator_number_ /= in_num;
        return std::nullopt;
    }

    std::optional<Error> Pow(double exp){

        std::optional<Error> is_calc=std::nullopt;
        accumulator_number_ = pow(accumulator_number_, exp);
        return std::optional(is_calc);
    }

private:
    double accumulator_number_ = 0;
    std::optional<double> memory_number_;
};
