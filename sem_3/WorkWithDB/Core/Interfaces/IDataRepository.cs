﻿namespace Core.Interfaces;

public interface IDataRepository<T>
{
    T? GetById(int id);
    IEnumerable<T> GetAll();
    
    void Add(T entity);

    void Update(T entity);

    void Delete(T entity);
}

