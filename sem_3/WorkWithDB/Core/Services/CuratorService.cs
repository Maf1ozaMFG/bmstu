using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Core.Interfaces;
using DatabaseModels;

namespace Core.Services;

public class CuratorService
{
    private readonly IDataRepository<Curator> _curatorRepository;
    private readonly IDataRepository<Group> _groupRepository;

    public CuratorService(IDataRepository<Curator> curatorRepository, IDataRepository<Group> groupRepository)
    {
        _curatorRepository = curatorRepository;
        _groupRepository = groupRepository;
    }

    public void CreateCurator(string name, string email)
    {
        try
        {
            var curator = new Curator 
            { 
                Name = name,
                Email = email
            };
            _curatorRepository.Add(curator);
        }
        catch (Exception ex)
        {
            throw new Exception(ex.Message);
        }
    }

    public void UpdateCuratorNameById(int id, string name)
    {
        try
        {
            var curator = _curatorRepository.GetById(id);
            if (curator != null)
            {
                curator.Name = name;
                _curatorRepository.Update(curator);
            }
            else
            {
                throw new Exception("Cannot find curator by this ID");
            }
        }
        catch (Exception ex)
        {
            throw new Exception(ex.Message);
        }
    }

    public Curator GetById(int id)
    {
        try
        {
            var curator = _curatorRepository.GetById(id);
            return curator ?? throw new Exception("Cannot find curator by this ID");
        }
        catch (Exception ex)
        {
            throw new Exception(ex.Message);
        }
    }

    public IEnumerable<Curator> GetAllCurators()
    {
        try
        {
            return _curatorRepository.GetAll();
        }
        catch (Exception ex)
        {
            throw new Exception(ex.Message);
        }
    }

    public void DeleteCuratorById(int id)
    {
        try
        {
            var curator = _curatorRepository.GetById(id);
            if (curator == null)
                throw new Exception("Cannot find curator by this ID");

            _curatorRepository.Delete(curator);
        }
        catch (Exception ex)
        {
            throw new Exception(ex.Message);
        }
    }

    public string GetCuratorNameByStudentId(int studentId)
    {
        try
        {
            var student = _groupRepository.GetAll()
                .SelectMany(g => g.Students)
                .FirstOrDefault(s => s.Id == studentId);

            if (student == null)
                throw new Exception("Cannot find student by this ID");

            var group = _groupRepository.GetById(student.GroupId);
            if (group == null)
                throw new Exception("Cannot find group for this student");

            var curator = _curatorRepository.GetById(group.CuratorId ?? throw new Exception("Group has no curator"));
            return curator?.Name ?? throw new Exception("Cannot find curator for this group");
        }
        catch (Exception ex)
        {
            throw new Exception(ex.Message);
        }
    }

    public void AssignToGroup(int curatorId, int groupId)
    {
        try
        {
            var curator = _curatorRepository.GetById(curatorId);
            if (curator == null)
                throw new Exception("Cannot find curator by this ID");

            var group = _groupRepository.GetById(groupId);
            if (group == null)
                throw new Exception("Cannot find group by this ID");

            group.CuratorId = curatorId;
            _groupRepository.Update(group);
        }
        catch (Exception ex)
        {
            throw new Exception(ex.Message);
        }
    }
}
