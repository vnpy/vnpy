ensure_pkgs = function(){
    if (!'data.table' %in% installed.packages()){
        install.packages('data.table')
    }
    if (!'rmongodb' %in% installed.packages()){
        install.packages('rmongodb')
    }
    require(data.table)
    require(rmongodb)
    return(1)
}

get_connection = function(){
    client = mongo.create()
    return(client)
}

get_dbs = function(){
    client = mongo.create()
    if(mongo.is.connected(client) == TRUE) {
        dbs = mongo.get.databases(client)
    }
    return(dbs)
}

get_colls = function(db){
    client = mongo.create()
    if(mongo.is.connected(client) == TRUE) {
        colls = mongo.get.database.collections(client, db)
    }
    return(colls)
}

view_doc = function(coll, one=1){
    client = mongo.create()
    if(mongo.is.connected(client) == TRUE) {
        if(one==1){
            doc = mongo.find.one(client, coll)
        }
        else{
            doc = mongo.find.all(client, coll)
        }
    }
    return(doc)
}

fetch = function(coll, start, end){
    client = mongo.create()
    if(mongo.is.connected(client) == TRUE) {
        docs = mongo.find.all(client, coll,
                              query = list(
                                  'date'=list('lte'=end),
                                  'date'=list('gte'=start)
                              ))
    }
    return(docs)
}

