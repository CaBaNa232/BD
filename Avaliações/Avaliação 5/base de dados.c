CREATE TABLE pessoa (

    --Colunas

    cod_pessoa SERIAL,
    nome_pes VARCHAR(50) NOT NULL,
    end_pes VARCHAR(100),
    tipo_pes VARCHAR(8),

    --Restrições

    CONSTRAINT pessoa_pk PRIMARY KEY(cod_pessoa),
    CONSTRAINT tipo_pessoa CHECK (tipo_pes IN ('medico','paciente'))
);

CREATE TABLE medico(

    --Colunas
    cod_pessoa INTEGER,
    CRM INTEGER NOT NULL,

    --Restrições
    CONSTRAINT medico_pk PRIMARY KEY(cod_pessoa),
    CONSTRAINT medico_fk FOREIGN KEY(cod_pessoa) 
        REFERENCES pessoa (cod_pessoa)
            ON DELETE ON UPDATE CASCADE
);


CREATE TABLE paciente(
    
    cod_pessoa INTEGER,
    nro_plano_saude INTEGER,

    
    CONSTRAINT paciente_pk PRIMARY KEY(cod_pessoa),
    CONSTRAINT paciente_fk FOREIGN KEY(cod_pessoa)
        REFERENCES pessoa (cod_pessoa)
            ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TABLE 

ALTER TABLE medico ADD especializacao VARCHAR(12) CONSTRAINT especializacao_check CHECK (especializacao IN ('graduado','especialista','mestrado','doutourado'));


SELECT pe.nome_pes, med.CRM FROM pessoa as pe, medico as med WHERE tipo_pessoa = 'medico' AND pe.cod_pessoa = med.cod_pessoa;

SELECT pe.nome_pes FROM pessoa as pe WHERE tipo_pessoa = 'paciente' INTERSECT SELECT pe.nome_pes FROM pessoa as pe WHERE tipo_pessoa = 'medico';

INSERT INTO pessoa (nome_pes, end_pes, tipo_pessoa) VALUES ('Jose Bras', 'Rua Julio Cotrim 371', 'medico');
INSERT INTO medico (cod_pessoa, CRM) VALUES ((SELECT cod_pessoa FROM pessoa WHERE nome_pes = 'Jose Bras'), 213105);

CREATE TABLE atendimento(
	
	cod_medico INTEGER NOT NULL,
	cod_paciente INTEGER NOT NULL,
	data date,
	hora TIME,
	descricao TEXT NOT NULL,
	valor NUMERIC(8,2) NOT NULL,
	
	CONSTRAINT atendimento_pk PRIMARY KEY(cod_medico, cod_paciente, data, hora),
	CONSTRAINT cod_medico_fk FOREIGN key(cod_medico)
		REFERENCES medico (cod_pessoa)
			ON DELETE NO ACTION ON UPDATE CASCADE,
	CONSTRAINT cod_paciente FOREIGN KEY (cod_paciente)
		REFERENCES paciente (cod_pessoa)
			ON DELETE CASCADE ON UPDATE CASCADE
);


SELECT DISTINCT aten.data, aten.hora FROM atendimento as aten, paciente as pa WHERE pa.nro_plano_saude = 145628 ORDER BY aten.data, aten.hora DESC;

INSERT INTO atendimento (cod_medico, cod_paciente, data, hora, descricao, valor) VALUES(5, 11, '2021-04-02', '18:00', 'Retorno', 100.00);

//Questão 2
INSERT INTO pessoa (nome_pes, end_pes, tipo_pessoa) VALUES ('Jose Bras', 'Rua Julio Cotrim 371', 'medico');
INSERT INTO medico (cod_pessoa, CRM) VALUES ((SELECT cod_pessoa FROM pessoa WHERE nome_pes = 'Jose Bras'), 213105);

//Recupere a quantidade de atendimentos feitos pelo médico chamado ‘Gabriel das Graças’.
SELECT COUNT(cod_medico) FROM atendimento as aten, pessoa as pa WHERE pa.cod_pessoa = aten.cod_medico AND pa. nome_pes = 
'Gabriel das Graças';

SELECT AVG(aten.valor) FROM atendimento as aten, pessoa as pa WHERE pa.nome_pes LIKE 'And%'; 
//Recupere o valor médio dos atendimentos dos pacientes que possuem nome iniciados com ‘And’.