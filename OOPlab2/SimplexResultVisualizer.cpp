#include "SimplexResultVisualizer.h"
#include <vector>
#include <QBoxLayout>
#include <iostream>

SimplexResultVisualizer::SimplexResultVisualizer()
{

}

QWidget* SimplexResultVisualizer::visualizeSimplexResult(const SimplexMethodSolution& simplex_solution){
    this->simplex_solution = simplex_solution;

    calcVarsNames(simplex_solution.getCoefs().size());

    QBoxLayout* layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom);
    layout->setSpacing(10);

    // visualize function
    layout->addWidget(visualizeFunction());

    // visualize all steps
    std::vector<SimplexMethodTable> steps = simplex_solution.getSteps();
    for(const auto& step : steps){
        layout->addWidget(visualizeSimplexTable(step));
    }

    // visualize result
    layout->addWidget(visualizeOptimalValues());



    QWidget* w = new QWidget();
    w->setLayout(layout);

    return w;

}


QTableWidget* SimplexResultVisualizer::visualizeSimplexTable(const SimplexMethodTable& simplex_step){
    std::size_t n_rows = simplex_step.getConstraintMatrix().nRows() + 1;
    std::size_t n_cols = simplex_step.getConstraintMatrix().nCols() + 4;

    QTableWidget* table = new QTableWidget(n_rows, n_cols);

    // set header

    QFont font = table->horizontalHeader()->font();
    font.setPointSize( 16 );
    table->horizontalHeader()->setFont( font );

    QVector<QString> colnames = {"c_basis","x_basis"};
    colnames.append(this->vars_names);
    colnames.append({QString::fromUtf8("\u03B2"), QString::fromUtf8("\u03B8")}); // beta and theta

    table->setHorizontalHeaderLabels(colnames);
    table->verticalHeader()->setVisible(false);

//    std::cout << table->rowHeight(0) << std::endl;
    table->setMinimumHeight((n_rows + 1) * 50); // for scroll line not to appear


    // set c_basis and x_basis columns
    auto basis_vars = simplex_step.getBasisVars();
    auto coefs = simplex_solution.getCoefs();
    auto beta = simplex_step.getBeta();

    for (std::size_t i = 0; i < n_rows - 1; i++){
        QString basis_coeff = QString::number(coefs[basis_vars[i]]);
        QString basis_var_name = vars_names[basis_vars[i]];
        QString cur_beta = QString::number(beta[i]);

        table->setItem(i, 0, new QTableWidgetItem(basis_coeff));
        table->setItem(i, 1, new QTableWidgetItem(basis_var_name));
        table->setItem(i, n_cols - 2, new QTableWidgetItem(cur_beta));
    }

    // set delta
    table->setItem(n_rows - 1, 1, new QTableWidgetItem(QString::fromUtf8("\u0394")));
    auto delta = simplex_step.getDelta();
    for (std::size_t j = 2; j < n_cols - 2; j++){
         QString cur_delta = QString::number(delta[j-2]);
         table->setItem(n_rows - 1, j, new QTableWidgetItem(cur_delta));
    }

    // set matrix
    auto matrix = simplex_step.getConstraintMatrix();
    for (std::size_t i = 0; i < matrix.nRows(); i++){
        for (std::size_t j = 0; j < matrix.nCols(); j++){
            QString cur_matrix_item = QString::number(matrix.item(i, j));
            table->setItem(i, j + 2,new QTableWidgetItem(cur_matrix_item));
        }
    }


    // set theta if it isn't last step
    if(!simplex_step.isLastStep()){
        auto theta = simplex_step.getTheta();

        for (std::size_t i = 0; i < n_rows - 1; i++){
            QString cur_theta = QString::number(beta[i]);
            table->setItem(i, n_cols - 1, new QTableWidgetItem(cur_theta));
        }

        // change color of lead item to red
        std::size_t lead_row = simplex_step.getLeadItem().first;
        std::size_t lead_col = simplex_step.getLeadItem().second;

        QTableWidgetItem* lead_item = table->item(lead_row, lead_col + 2); // change
        lead_item->setForeground(QBrush(QColor(245, 66, 84)));
    }

    return table;
}

void SimplexResultVisualizer::calcVarsNames(std::size_t number_of_variables){
    for (std::size_t i = 0; i < number_of_variables; i++){
        this->vars_names.push_back("x" + QString::number(i+1));
    }
}


QLabel* SimplexResultVisualizer::visualizeFunction(){
    QString str = "L(x) = ";

    std::vector<double> coefs = simplex_solution.getCoefs();

    str += QString::number(coefs[0]) + "*" + vars_names[0];
    for (std::size_t i = 1; i < coefs.size(); i++){
        if (coefs[i] >= 0){
            str += " + ";
        }
        else{
            str += "  ";
        }

        str += QString::number(coefs[i]) + "*" + vars_names[i];
    }

    str += " -> min";

    QLabel* label = new QLabel(str);

    return label;
}

QLabel* SimplexResultVisualizer::visualizeOptimalValues(){
    QString str;

    if (simplex_solution.isSolutionExist()){
        str += "Solution:\n";

        std::vector<double> optimal_vars_values = simplex_solution.getSolution();

        for (std::size_t i = 0; i < optimal_vars_values.size(); i++){
            str += vars_names[i] + " = " + QString::number(optimal_vars_values[i]) + "\n";
        }
        str += "\n L(x*) = " + QString::number(simplex_solution.getFuncValue());
    }
    else{
        str += "Function is unlimited on D, so solution doen not exist\n";
    }

    QLabel* label = new QLabel(str);

    return label;
}
