/*
 * table.cpp
 *
 *  Created on: 2013-9-22
 *      Author: liyongfeng
 */

#include "table.h"
// ColumnDescriptor
ProjectionDescriptor::ProjectionDescriptor():projection_id_(){
}

ProjectionDescriptor::ProjectionDescriptor(const string& name)
:Projection_name_(name){
	// Check if hdfsfile already exists
	// Meanwhile create a hsfsfile to store this column's data.
}

ProjectionDescriptor::~ProjectionDescriptor(){

}
void ProjectionDescriptor::addAttribute(Attribute attr)
{
	attribute_list_.push_back(attr);
}

bool ProjectionDescriptor::isExist(const string& name) const
{
	for(unsigned i=0;i<attribute_list_.size();i++){
		if(attribute_list_[i].attrName==name) return true;
	}
	return false;
}

// TableDescritptor
TableDescriptor::TableDescriptor(const string& name, const TableID table_id)
: tableName(name),table_id_(table_id){

}

TableDescriptor::~TableDescriptor(){

}

void TableDescriptor::addAttribute(Attribute attr)
{
	attributes.push_back(attr);
}
bool TableDescriptor::addAttribute(string attname,data_type dt,unsigned max_length){
	/*check for attribute rename*/
	for(unsigned i=0;i<attributes.size();i++){
		if(attributes[i].attrName==attname)
			return false;
	}
	Attribute att(table_id_,attributes.size(),attname,dt,max_length);
	attributes.push_back(att);
	return true;
}

void TableDescriptor::addColumn(ProjectionDescriptor* column)
{
//	ColumnID current = (ColumnID)columns.size();
//	column->setColumnID(current);
//	columns[current] = column;
}
void TableDescriptor::addProjection(vector<ColumnID> id_list){
	ProjectionDescriptor* projection=new ProjectionDescriptor();
	for(unsigned i=0;i<id_list.size();i++){
		projection->addAttribute(attributes[id_list[i]]);
	}
}

bool TableDescriptor::createHashPartitionedProjection(vector<ColumnID> column_list,ColumnID partition_key_index,unsigned number_of_partitions){
	ProjectionDescriptor *projection=new ProjectionDescriptor();
	projection->projection_id_=projection_list_.size();
	for(unsigned i=0;i<column_list.size();i++){
		projection->addAttribute(attributes[column_list[i]]);
	}

	PartitionFunction* hash_function=PartitionFunctionFactory::createModuloFunction(number_of_partitions);
	projection->partitioner=new Partitioner(number_of_partitions,attributes[partition_key_index],hash_function);



	projection_list_.push_back(projection);

}

bool TableDescriptor::isExist(const string& name) const
{
	for(unsigned i=0;i<attributes.size();i++){
		if(attributes[i].attrName==name) return true;
	}
	return false;
}

map<string, set<string> > TableDescriptor::getColumnLocations(const string& attrName) const
{
//	hashmap<string, set<string> > result;
//
//	foreachvalue(ColumnDescriptor* cd, columns)
//	{
//		if(cd->isExist(attrName))
//		{
//			result = cd->getFileLocations();
//			break;
//		}
//	}
//	return result;
}

ProjectionDescriptor* TableDescriptor::getProjectoin(ProjectionID pid)const{
	if(pid>=0||pid<projection_list_.size()){
		return projection_list_[pid];
	}
	return NULL;
}
